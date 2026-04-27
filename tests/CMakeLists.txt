include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(sudoku_tests
    test_board.cpp
    test_solver.cpp
    test_validator.cpp
    test_generator.cpp
)

target_link_libraries(sudoku_tests
    PRIVATE
        sudoku_core
        Catch2::Catch2WithMain
        project_warnings
        project_sanitizers
)

# Treat Catch2 headers as system includes to suppress third-party warnings
get_target_property(CATCH2_INCLUDE_DIRS Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(sudoku_tests SYSTEM PRIVATE ${CATCH2_INCLUDE_DIRS})

include(CTest)
include(Catch)
catch_discover_tests(sudoku_tests)
