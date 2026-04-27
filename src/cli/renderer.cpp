#include "renderer.h"

#include <iostream>

namespace sudoku::cli {

namespace {
constexpr const char* kReset = "\033[0m";
constexpr const char* kBold = "\033[1m";
constexpr const char* kDim = "\033[2m";
constexpr const char* kCyan = "\033[36m";
constexpr const char* kYellow = "\033[33m";
constexpr const char* kGreen = "\033[32m";
}  // namespace

void Renderer::drawBoard(const Board& board) {
    std::cout << "\n    ";
    for (int c = 1; c <= sudoku::kBoardSize; ++c) {
        std::cout << " " << c << " ";
        if (c % sudoku::kBoxSize == 0 && c < sudoku::kBoardSize) {
            std::cout << "  ";
        }
    }
    std::cout << "\n   " << kDim;
    for (int i = 0; i < 33; ++i) {
        std::cout << '-';
    }
    std::cout << kReset << "\n";

    for (int r = 0; r < sudoku::kBoardSize; ++r) {
        if (r > 0 && r % sudoku::kBoxSize == 0) {
            std::cout << "   " << kDim;
            for (int i = 0; i < 33; ++i) {
                std::cout << '-';
            }
            std::cout << kReset << "\n";
        }

        std::cout << " " << (r + 1) << " " << kDim << "|" << kReset;
        for (int c = 0; c < sudoku::kBoardSize; ++c) {
            if (c > 0 && c % sudoku::kBoxSize == 0) {
                std::cout << kDim << "|" << kReset;
            }

            int val = board.cellAt(r, c);
            if (val == sudoku::kEmptyCell) {
                std::cout << " . ";
            } else if (board.isLocked(r, c)) {
                std::cout << " " << kBold << kCyan << val << kReset << " ";
            } else {
                std::cout << " " << kYellow << val << kReset << " ";
            }
        }
        std::cout << kDim << "|" << kReset << "\n";
    }

    std::cout << "   " << kDim;
    for (int i = 0; i < 33; ++i) {
        std::cout << '-';
    }
    std::cout << kReset << "\n";
}

void Renderer::drawWelcome() {
    std::cout << "\n"
              << kBold << kCyan << "  ===========================\n"
              << "       SUDOKU  CLI  v1.0\n"
              << "  ===========================\n"
              << kReset << "\n";
}

void Renderer::drawHelp() {
    std::cout << kDim << "  Commands:\n"
              << "    r c v   - Place value v at row r, col c (1-9)\n"
              << "    u       - Undo last move\n"
              << "    s       - Solve the board\n"
              << "    n       - New game\n"
              << "    h       - Show this help\n"
              << "    q       - Quit\n"
              << kReset << "\n";
}

void Renderer::drawMessage(const char* message) {
    std::cout << "\n  " << kYellow << message << kReset << "\n";
}

void Renderer::drawVictory() {
    std::cout << "\n  " << kBold << kGreen << "Congratulations! Puzzle solved!" << kReset << "\n\n";
}

}  // namespace sudoku::cli
