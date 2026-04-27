#include <sudoku/validator.h>

#include <catch2/catch_test_macros.hpp>

using namespace sudoku;

TEST_CASE("Valid placement on empty board", "[validator]") {
    Board board;
    REQUIRE(Validator::isValidPlacement(board, 0, 0, 5));
}

TEST_CASE("Duplicate in row is invalid", "[validator]") {
    Board board;
    board.setCell(0, 0, 5);
    REQUIRE_FALSE(Validator::isValidPlacement(board, 0, 8, 5));
}

TEST_CASE("Duplicate in column is invalid", "[validator]") {
    Board board;
    board.setCell(0, 0, 3);
    REQUIRE_FALSE(Validator::isValidPlacement(board, 8, 0, 3));
}

TEST_CASE("Duplicate in box is invalid", "[validator]") {
    Board board;
    board.setCell(0, 0, 7);
    REQUIRE_FALSE(Validator::isValidPlacement(board, 2, 2, 7));
}

TEST_CASE("Out-of-range values are invalid", "[validator]") {
    Board board;
    REQUIRE_FALSE(Validator::isValidPlacement(board, 0, 0, 0));
    REQUIRE_FALSE(Validator::isValidPlacement(board, 0, 0, 10));
}

TEST_CASE("Empty board is valid", "[validator]") {
    Board board;
    REQUIRE(Validator::isBoardValid(board));
}

TEST_CASE("Empty board is not solved", "[validator]") {
    Board board;
    REQUIRE_FALSE(Validator::isSolved(board));
}

TEST_CASE("Known solved board validates correctly", "[validator]") {
    Grid grid = {{
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9},
    }};
    Board board(grid);
    REQUIRE(Validator::isBoardValid(board));
    REQUIRE(Validator::isSolved(board));
}
