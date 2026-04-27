#include <sudoku/board.h>

#include <catch2/catch_test_macros.hpp>

using namespace sudoku;

TEST_CASE("Default board is empty", "[board]") {
    Board board;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            REQUIRE(board.cellAt(r, c) == kEmptyCell);
            REQUIRE(board.isEmpty(r, c));
            REQUIRE_FALSE(board.isLocked(r, c));
        }
    }
    REQUIRE_FALSE(board.isFull());
}

TEST_CASE("Set and clear cells", "[board]") {
    Board board;
    REQUIRE(board.setCell(0, 0, 5));
    REQUIRE(board.cellAt(0, 0) == 5);
    REQUIRE_FALSE(board.isEmpty(0, 0));

    board.clearCell(0, 0);
    REQUIRE(board.isEmpty(0, 0));
}

TEST_CASE("Locked cells cannot be modified", "[board]") {
    Board board;
    board.setCell(3, 4, 7);
    board.lockFilledCells();

    REQUIRE(board.isLocked(3, 4));
    REQUIRE_FALSE(board.setCell(3, 4, 9));
    REQUIRE(board.cellAt(3, 4) == 7);
}

TEST_CASE("Reset clears only unlocked cells", "[board]") {
    Board board;
    board.setCell(0, 0, 1);
    board.lockFilledCells();
    board.setCell(1, 1, 2);

    board.reset();
    REQUIRE(board.cellAt(0, 0) == 1);
    REQUIRE(board.cellAt(1, 1) == kEmptyCell);
}

TEST_CASE("Board from grid constructor", "[board]") {
    Grid grid{};
    grid[0][0] = 5;
    grid[8][8] = 3;

    Board board(grid);
    REQUIRE(board.cellAt(0, 0) == 5);
    REQUIRE(board.cellAt(8, 8) == 3);
    REQUIRE(board.cellAt(4, 4) == kEmptyCell);
}
