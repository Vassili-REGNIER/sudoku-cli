#pragma once

#include <sudoku/types.h>

#include <optional>
#include <vector>

namespace sudoku {

/// Immutable-friendly board representation.
/// Stores a 9x9 grid and tracks which cells are part of the original puzzle
/// (locked) vs. player-placed (mutable).
class Board {
public:
    Board();
    explicit Board(const Grid& initial);

    [[nodiscard]] Cell cellAt(int row, int col) const;
    [[nodiscard]] bool isLocked(int row, int col) const;
    [[nodiscard]] bool isEmpty(int row, int col) const;
    [[nodiscard]] bool isFull() const;
    [[nodiscard]] const Grid& grid() const;

    bool setCell(int row, int col, Cell value);
    void clearCell(int row, int col);
    void reset();

    /// Lock all non-empty cells, marking them as part of the original puzzle.
    void lockFilledCells();

private:
    Grid grid_{};
    std::array<std::array<bool, kBoardSize>, kBoardSize> locked_{};
};

}  // namespace sudoku
