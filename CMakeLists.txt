cmake_minimum_required(VERSION 3.20)

project(
    sudoku
    VERSION 1.0.0
    DESCRIPTION "A production-ready CLI Sudoku game in modern C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Options
option(ENABLE_SANITIZERS "Enable ASan and UBSan for Debug builds" OFF)
option(BUILD_TESTING "Build the test suite" ON)

# Compiler warnings – treat warnings seriously in CI
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:
        -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
        -Wold-style-cast -Wcast-align -Woverloaded-virtual
        -Wconversion -Wsign-conversion -Wnull-dereference
        -Wformat=2
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /permissive-
    >
)

# Sanitizers (Debug only)
add_library(project_sanitizers INTERFACE)
if(ENABLE_SANITIZERS)
    target_compile_options(project_sanitizers INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>
    )
    target_link_options(project_sanitizers INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
endif()

# Core library
add_library(sudoku_core STATIC
    src/core/board.cpp
    src/core/solver.cpp
    src/core/generator.cpp
    src/core/validator.cpp
)
target_include_directories(sudoku_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sudoku_core
    PRIVATE project_warnings project_sanitizers
)

# CLI executable
add_executable(sudoku
    src/cli/main.cpp
    src/cli/renderer.cpp
    src/cli/input_handler.cpp
    src/cli/game.cpp
)
target_link_libraries(sudoku
    PRIVATE sudoku_core project_warnings project_sanitizers
)

# Tests
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
