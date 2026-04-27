#pragma once

#include <sudoku/board.h>

#include <optional>

namespace sudoku {

/// Constraint-propagation + backtracking solver.
class Solver {
public:
    /// Attempt to solve the board in place. Returns true on success.
    [[nodiscard]] static bool solve(Board& board);

    /// Returns a solved copy, leaving the original untouched.
    [[nodiscard]] static std::optional<Board> solved(const Board& board);

    /// Check whether the puzzle has exactly one solution.
    [[nodiscard]] static bool hasUniqueSolution(const Board& board);
};

}  // namespace sudoku
