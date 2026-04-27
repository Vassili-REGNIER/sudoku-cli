#include <sudoku/solver.h>
#include <sudoku/validator.h>

#include <catch2/catch_test_macros.hpp>

using namespace sudoku;

TEST_CASE("Solve an empty board", "[solver]") {
    Board board;
    REQUIRE(Solver::solve(board));
    REQUIRE(Validator::isSolved(board));
}

TEST_CASE("Solve a partially filled board", "[solver]") {
    Grid grid{};
    grid[0] = {5, 3, 0, 0, 7, 0, 0, 0, 0};
    grid[1] = {6, 0, 0, 1, 9, 5, 0, 0, 0};
    grid[2] = {0, 9, 8, 0, 0, 0, 0, 6, 0};
    grid[3] = {8, 0, 0, 0, 6, 0, 0, 0, 3};
    grid[4] = {4, 0, 0, 8, 0, 3, 0, 0, 1};
    grid[5] = {7, 0, 0, 0, 2, 0, 0, 0, 6};
    grid[6] = {0, 6, 0, 0, 0, 0, 2, 8, 0};
    grid[7] = {0, 0, 0, 4, 1, 9, 0, 0, 5};
    grid[8] = {0, 0, 0, 0, 8, 0, 0, 7, 9};

    Board board(grid);
    REQUIRE(Solver::solve(board));
    REQUIRE(Validator::isSolved(board));
}

TEST_CASE("solved() returns a copy without modifying the original", "[solver]") {
    Board board;
    board.setCell(0, 0, 5);

    auto result = Solver::solved(board);
    REQUIRE(result.has_value());
    REQUIRE(Validator::isSolved(result.value()));
    REQUIRE(board.cellAt(0, 1) == kEmptyCell);
}

TEST_CASE("Unique solution detection", "[solver]") {
    Grid grid{};
    grid[0] = {5, 3, 0, 0, 7, 0, 0, 0, 0};
    grid[1] = {6, 0, 0, 1, 9, 5, 0, 0, 0};
    grid[2] = {0, 9, 8, 0, 0, 0, 0, 6, 0};
    grid[3] = {8, 0, 0, 0, 6, 0, 0, 0, 3};
    grid[4] = {4, 0, 0, 8, 0, 3, 0, 0, 1};
    grid[5] = {7, 0, 0, 0, 2, 0, 0, 0, 6};
    grid[6] = {0, 6, 0, 0, 0, 0, 2, 8, 0};
    grid[7] = {0, 0, 0, 4, 1, 9, 0, 0, 5};
    grid[8] = {0, 0, 0, 0, 8, 0, 0, 7, 9};

    Board board(grid);
    REQUIRE(Solver::hasUniqueSolution(board));
}
