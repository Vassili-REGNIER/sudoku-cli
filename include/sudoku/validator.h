#pragma once

#include <sudoku/board.h>

namespace sudoku {

/// Stateless validation utilities for Sudoku rules.
class Validator {
public:
    [[nodiscard]] static bool isValidPlacement(const Board& board, int row, int col, Cell value);
    [[nodiscard]] static bool isRowValid(const Board& board, int row);
    [[nodiscard]] static bool isColValid(const Board& board, int col);
    [[nodiscard]] static bool isBoxValid(const Board& board, int box_row, int box_col);
    [[nodiscard]] static bool isBoardValid(const Board& board);
    [[nodiscard]] static bool isSolved(const Board& board);
};

}  // namespace sudoku
