#!/usr/bin/env bash
# Run clang-tidy on project sources using compile_commands.json from build/.
#
# Prerequisites:
#   cmake -B build
#
# Optional: unpack clang-tidy-18 + libclang-cpp18 + libllvm18 debs under .tools/llvm-18
# (see README). Otherwise uses clang-tidy from PATH if installed system-wide.
#
# Passes GCC's libstdc++ internal include directory so Clang can parse TUs built with g++.
# Appends path regexes so FetchContent targets (e.g. Catch2) are skipped.

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GCC_BIN="$(command -v gcc-13 || command -v gcc)"
GCC_INC="$("${GCC_BIN}" -print-file-name=include)"

RUN_CLANG_TIDY="$(command -v run-clang-tidy || command -v run-clang-tidy-18 || command -v run-clang-tidy-17 ||
    true)"
if [[ -z "${RUN_CLANG_TIDY}" ]]; then
    echo "error: run-clang-tidy not found (install clang-tidy / clang-tools-extra)" >&2
    exit 1
fi

TOOLS="${ROOT}/.tools/llvm-18"
export PATH="${TOOLS}/usr/lib/llvm-18/bin:${PATH}"
export LD_LIBRARY_PATH="${TOOLS}/usr/lib/x86_64-linux-gnu:${TOOLS}/usr/lib/llvm-18/lib:${LD_LIBRARY_PATH:-}"

CT="${TOOLS}/usr/lib/llvm-18/bin/clang-tidy"
if [[ ! -x "${CT}" ]]; then
    CT="$(command -v clang-tidy || command -v clang-tidy-18 || command -v clang-tidy-17 || true)"
fi
if [[ -z "${CT}" ]] || [[ ! -x "${CT}" ]]; then
    echo "error: clang-tidy not found (install clang-tidy or clang-tidy-18)" >&2
    exit 1
fi

EXTRA_BEFORE=("-extra-arg-before=-isystem${GCC_INC}")

ROOT_RE="$(printf '%s' "${ROOT}" | sed 's/[.[*^$()+?{|]/\\&/g')"
DEFAULT_PATTERNS=(".*${ROOT_RE}/src/.*" ".*${ROOT_RE}/include/.*" ".*${ROOT_RE}/tests/.*")

exec "${RUN_CLANG_TIDY}" -p "${ROOT}/build" \
    -clang-tidy-binary "${CT}" \
    "${EXTRA_BEFORE[@]}" \
    "$@" \
    "${DEFAULT_PATTERNS[@]}"
