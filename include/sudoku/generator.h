#pragma once

#include <sudoku/board.h>

namespace sudoku {

/// Generates valid Sudoku puzzles by constructing a full solution and then
/// removing cells to reach the desired difficulty while ensuring uniqueness.
class Generator {
public:
    [[nodiscard]] static Board generate(Difficulty difficulty);

private:
    static bool fillBoard(Board& board);
    static void removeClues(Board& board, int clues_to_remove);
};

}  // namespace sudoku
