#pragma once

#include <sudoku/board.h>

namespace sudoku::cli {

/// Renders the Sudoku board to stdout with box separators and color hints.
class Renderer {
public:
    static void drawBoard(const Board& board);
    static void drawWelcome();
    static void drawHelp();
    static void drawMessage(const char* message);
    static void drawVictory();
};

}  // namespace sudoku::cli
