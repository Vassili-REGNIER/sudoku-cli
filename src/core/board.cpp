#include <sudoku/board.h>

#include <cstddef>

namespace sudoku {

Board::Board() = default;

Board::Board(const Grid& initial) : grid_(initial) {
    for (auto& row : locked_) {
        row.fill(false);
    }
}

Cell Board::cellAt(int row, int col) const {
    return grid_.at(static_cast<size_t>(row)).at(static_cast<size_t>(col));
}

bool Board::isLocked(int row, int col) const {
    return locked_.at(static_cast<size_t>(row)).at(static_cast<size_t>(col));
}

bool Board::isEmpty(int row, int col) const {
    return cellAt(row, col) == kEmptyCell;
}

bool Board::isFull() const {
    for (const auto& row : grid_) {
        for (auto cell : row) {
            if (cell == kEmptyCell) {
                return false;
            }
        }
    }
    return true;
}

const Grid& Board::grid() const {
    return grid_;
}

bool Board::setCell(int row, int col, Cell value) {
    if (isLocked(row, col)) {
        return false;
    }
    grid_.at(static_cast<size_t>(row)).at(static_cast<size_t>(col)) = value;
    return true;
}

void Board::clearCell(int row, int col) {
    if (!isLocked(row, col)) {
        grid_.at(static_cast<size_t>(row)).at(static_cast<size_t>(col)) = kEmptyCell;
    }
}

void Board::reset() {
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (!isLocked(r, c)) {
                grid_.at(static_cast<size_t>(r)).at(static_cast<size_t>(c)) = kEmptyCell;
            }
        }
    }
}

void Board::lockFilledCells() {
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (grid_.at(static_cast<size_t>(r)).at(static_cast<size_t>(c)) != kEmptyCell) {
                locked_.at(static_cast<size_t>(r)).at(static_cast<size_t>(c)) = true;
            }
        }
    }
}

}  // namespace sudoku
