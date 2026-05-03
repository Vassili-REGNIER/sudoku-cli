#include <sudoku/validator.h>

#include <array>
#include <cstddef>

namespace sudoku {

bool Validator::isValidPlacement(const Board& board, int row, int col, Cell value) {
    if (value < 1 || value > kBoardSize) {
        return false;
    }

    for (int c = 0; c < kBoardSize; ++c) {
        if (c != col && board.cellAt(row, c) == value) {
            return false;
        }
    }

    for (int r = 0; r < kBoardSize; ++r) {
        if (r != row && board.cellAt(r, col) == value) {
            return false;
        }
    }

    int box_r = (row / kBoxSize) * kBoxSize;
    int box_c = (col / kBoxSize) * kBoxSize;
    for (int r = box_r; r < box_r + kBoxSize; ++r) {
        for (int c = box_c; c < box_c + kBoxSize; ++c) {
            if (r != row && c != col && board.cellAt(r, c) == value) {
                return false;
            }
        }
    }

    return true;
}

bool Validator::isRowValid(const Board& board, int row) {
    std::array<bool, kBoardSize + 1> seen{};
    for (int c = 0; c < kBoardSize; ++c) {
        Cell v = board.cellAt(row, c);
        if (v == kEmptyCell) {
            continue;
        }
        if (v < 1 || v > kBoardSize || seen.at(static_cast<size_t>(v))) {
            return false;
        }
        seen.at(static_cast<size_t>(v)) = true;
    }
    return true;
}

bool Validator::isColValid(const Board& board, int col) {
    std::array<bool, kBoardSize + 1> seen{};
    for (int r = 0; r < kBoardSize; ++r) {
        Cell v = board.cellAt(r, col);
        if (v == kEmptyCell) {
            continue;
        }
        if (v < 1 || v > kBoardSize || seen.at(static_cast<size_t>(v))) {
            return false;
        }
        seen.at(static_cast<size_t>(v)) = true;
    }
    return true;
}

bool Validator::isBoxValid(const Board& board, int box_row, int box_col) {
    std::array<bool, kBoardSize + 1> seen{};
    for (int r = box_row; r < box_row + kBoxSize; ++r) {
        for (int c = box_col; c < box_col + kBoxSize; ++c) {
            Cell v = board.cellAt(r, c);
            if (v == kEmptyCell) {
                continue;
            }
            if (v < 1 || v > kBoardSize || seen.at(static_cast<size_t>(v))) {
                return false;
            }
            seen.at(static_cast<size_t>(v)) = true;
        }
    }
    return true;
}

bool Validator::isBoardValid(const Board& board) {
    for (int i = 0; i < kBoardSize; ++i) {
        if (!isRowValid(board, i) || !isColValid(board, i)) {
            return false;
        }
    }
    for (int r = 0; r < kBoardSize; r += kBoxSize) {
        for (int c = 0; c < kBoardSize; c += kBoxSize) {
            if (!isBoxValid(board, r, c)) {
                return false;
            }
        }
    }
    return true;
}

bool Validator::isSolved(const Board& board) {
    return board.isFull() && isBoardValid(board);
}

}  // namespace sudoku
