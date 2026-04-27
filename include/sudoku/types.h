#pragma once

#include <array>
#include <cstdint>

namespace sudoku {

constexpr int kBoardSize = 9;
constexpr int kBoxSize = 3;
constexpr int kEmptyCell = 0;

using Cell = int;
using Grid = std::array<std::array<Cell, kBoardSize>, kBoardSize>;

enum class Difficulty : std::uint8_t { Easy, Medium, Hard };

struct Position {
    int row;
    int col;
};

inline bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col;
}

}  // namespace sudoku
