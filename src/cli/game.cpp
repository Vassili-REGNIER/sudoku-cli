#include "game.h"

#include "input_handler.h"
#include "renderer.h"

#include <sudoku/generator.h>
#include <sudoku/solver.h>
#include <sudoku/validator.h>

#include <iostream>
#include <string>
#include <variant>

namespace sudoku::cli {

namespace {

Difficulty promptDifficulty() {
    std::cout << "  Select difficulty:\n"
              << "    1) Easy\n"
              << "    2) Medium\n"
              << "    3) Hard\n"
              << "  > ";

    std::string line;
    if (!std::getline(std::cin, line) || line.empty()) {
        return Difficulty::Medium;
    }

    switch (line[0]) {
        case '1':
            return Difficulty::Easy;
        case '3':
            return Difficulty::Hard;
        default:
            return Difficulty::Medium;
    }
}

}  // namespace

void Game::run() {
    Renderer::drawWelcome();
    Renderer::drawHelp();
    startNewGame();

    std::string line;
    bool quit = false;
    while (!quit) {
        std::cout << "  > ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        Command cmd = InputHandler::parse(line);

        std::visit(
            [this, &quit](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;

                if constexpr (std::is_same_v<T, PlaceCommand>) {
                    handlePlace(arg.row, arg.col, arg.value);
                } else if constexpr (std::is_same_v<T, UndoCommand>) {
                    handleUndo();
                } else if constexpr (std::is_same_v<T, SolveCommand>) {
                    handleSolve();
                } else if constexpr (std::is_same_v<T, NewGameCommand>) {
                    startNewGame();
                } else if constexpr (std::is_same_v<T, HelpCommand>) {
                    Renderer::drawHelp();
                } else if constexpr (std::is_same_v<T, QuitCommand>) {
                    std::cout << "  Goodbye!\n";
                    quit = true;
                } else if constexpr (std::is_same_v<T, InvalidCommand>) {
                    Renderer::drawMessage(arg.reason.c_str());
                }
            },
            cmd);
    }
}

void Game::startNewGame() {
    difficulty_ = promptDifficulty();
    history_.clear();

    std::cout << "  Generating puzzle...\n";
    board_ = Generator::generate(difficulty_);
    Renderer::drawBoard(board_);
}

void Game::handlePlace(int row, int col, int value) {
    if (board_.isLocked(row, col)) {
        Renderer::drawMessage("That cell is part of the original puzzle.");
        return;
    }

    if (!Validator::isValidPlacement(board_, row, col, value)) {
        Renderer::drawMessage("Invalid move: conflicts with Sudoku rules.");
        return;
    }

    history_.push_back({.row = row, .col = col, .previous_value = board_.cellAt(row, col)});
    board_.setCell(row, col, value);
    Renderer::drawBoard(board_);

    if (Validator::isSolved(board_)) {
        Renderer::drawVictory();
    }
}

void Game::handleUndo() {
    if (history_.empty()) {
        Renderer::drawMessage("Nothing to undo.");
        return;
    }

    auto [row, col, prev] = history_.back();
    history_.pop_back();

    if (prev == kEmptyCell) {
        board_.clearCell(row, col);
    } else {
        board_.setCell(row, col, prev);
    }
    Renderer::drawBoard(board_);
}

void Game::handleSolve() {
    auto result = Solver::solved(board_);
    if (result) {
        board_ = *result;
        Renderer::drawBoard(board_);
        Renderer::drawMessage("Board solved automatically.");
    } else {
        Renderer::drawMessage("No solution exists for the current board state.");
    }
}

}  // namespace sudoku::cli
