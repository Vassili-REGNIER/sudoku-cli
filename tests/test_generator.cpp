#include <sudoku/generator.h>
#include <sudoku/solver.h>
#include <sudoku/validator.h>

#include <catch2/catch_test_macros.hpp>

using namespace sudoku;

TEST_CASE("Generated Easy puzzle is valid and solvable", "[generator]") {
    Board board = Generator::generate(Difficulty::Easy);
    REQUIRE(Validator::isBoardValid(board));

    auto solved = Solver::solved(board);
    REQUIRE(solved.has_value());
    REQUIRE(Validator::isSolved(solved.value()));
}

TEST_CASE("Generated Medium puzzle is valid and solvable", "[generator]") {
    Board board = Generator::generate(Difficulty::Medium);
    REQUIRE(Validator::isBoardValid(board));

    auto solved = Solver::solved(board);
    REQUIRE(solved.has_value());
    REQUIRE(Validator::isSolved(solved.value()));
}

TEST_CASE("Generated puzzle has locked cells", "[generator]") {
    Board board = Generator::generate(Difficulty::Easy);

    bool has_locked = false;
    bool has_empty = false;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (board.isLocked(r, c)) {
                has_locked = true;
            }
            if (board.isEmpty(r, c)) {
                has_empty = true;
            }
        }
    }
    REQUIRE(has_locked);
    REQUIRE(has_empty);
}
