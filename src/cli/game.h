#pragma once

#include <sudoku/board.h>
#include <sudoku/types.h>

#include <vector>

namespace sudoku::cli {

/// Main game loop: ties together the core engine and CLI interface.
class Game {
public:
    void run();

private:
    void startNewGame();
    void handlePlace(int row, int col, int value);
    void handleUndo();
    void handleSolve();

    Board board_;
    Difficulty difficulty_ = Difficulty::Medium;

    struct Move {
        int row;
        int col;
        Cell previous_value;
    };
    std::vector<Move> history_;
};

}  // namespace sudoku::cli
