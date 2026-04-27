# Sudoku CLI

A production-ready command-line Sudoku game written in modern C++ (C++20).

## Features

- Generate Sudoku puzzles with configurable difficulty (Easy, Medium, Hard).
- Interactive CLI with undo support.
- Validate moves in real time; solve any valid board instantly.
- Clean architecture: core engine has zero I/O dependencies.

## Prerequisites

| Tool   | Minimum Version |
|--------|-----------------|
| CMake  | 3.20            |
| GCC    | 13 (or Clang 17)|
| Git    | 2.x             |

Catch2 v3 is fetched automatically via CMake `FetchContent`.

## Build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel $(nproc)
```

### Debug build with sanitizers

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build --parallel $(nproc)
```

## Test

```bash
cd build && ctest --output-on-failure
```

## Static analysis (clang-tidy)

Install LLVM's `clang-tidy` / `run-clang-tidy` on your system, **or** extract the official Ubuntu packages under `.tools/llvm-18` (see note below). Then:

```bash
cmake -B build
./scripts/run-clang-tidy.sh -j "$(nproc)"
```

The script prepends GCC's internal include directory (`gcc -print-file-name=include`) so Clang can parse translation units configured for `g++`. It restricts checks to `src/`, `include/`, and `tests/` so dependencies such as Catch2 are skipped.

**Optional local toolchain (no root):** download `clang-tidy-18`, `libclang-cpp18`, and `libllvm18` `.deb` packages for your Ubuntu version, extract them into the same prefix (e.g. `.tools/llvm-18` with `dpkg-deb -x`). The script will pick up `clang-tidy` from there.

## Usage

```bash
./build/sudoku
```

Follow the on-screen prompts to select difficulty, place numbers, undo moves, or request a solution.

### Controls

| Command          | Description                  |
|------------------|------------------------------|
| `r c v`          | Place value `v` at row `r`, column `c` (1-9) |
| `u`              | Undo the last move           |
| `s`              | Solve the current board      |
| `n`              | Start a new game             |
| `q`              | Quit                         |

## Project Structure

```
├── include/sudoku/   # Public headers (Core API)
├── src/core/         # Core game engine (Board, Solver, Generator, Validator)
├── src/cli/          # CLI user interface (Renderer, InputHandler, Game loop)
├── tests/            # Unit tests (Catch2)
├── .github/workflows # CI pipeline
└── CMakeLists.txt    # Build configuration
```

## License

MIT
