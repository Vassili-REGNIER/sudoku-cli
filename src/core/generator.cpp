#include <sudoku/generator.h>
#include <sudoku/solver.h>
#include <sudoku/validator.h>

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <random>
#include <vector>

namespace sudoku {

namespace {

std::mt19937& rng() {
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

int cluesToRemoveForDifficulty(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return 36;
        case Difficulty::Medium:
            return 46;
        case Difficulty::Hard:
            return 54;
    }
    return 46;
}

}  // namespace

bool Generator::fillBoard(Board& board) {
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (!board.isEmpty(r, c)) {
                continue;
            }

            std::vector<int> values(static_cast<std::size_t>(kBoardSize));
            std::iota(values.begin(), values.end(), 1);
            std::shuffle(values.begin(), values.end(), rng());

            for (const int v : values) {
                if (Validator::isValidPlacement(board, r, c, v)) {
                    board.setCell(r, c, v);
                    if (fillBoard(board)) {
                        return true;
                    }
                    board.clearCell(r, c);
                }
            }
            return false;
        }
    }
    return true;
}

void Generator::removeClues(Board& board, int clues_to_remove) {
    const auto cell_count =
        static_cast<std::size_t>(kBoardSize) * static_cast<std::size_t>(kBoardSize);
    std::vector<int> positions(cell_count);
    std::iota(positions.begin(), positions.end(), 0);
    std::shuffle(positions.begin(), positions.end(), rng());

    int removed = 0;
    for (const int pos : positions) {
        if (removed >= clues_to_remove) {
            break;
        }

        const int r = pos / kBoardSize;
        const int c = pos % kBoardSize;

        const Cell backup = board.cellAt(r, c);
        if (backup == kEmptyCell) {
            continue;
        }

        board.clearCell(r, c);

        if (Solver::hasUniqueSolution(board)) {
            ++removed;
        } else {
            board.setCell(r, c, backup);
        }
    }
}

Board Generator::generate(Difficulty difficulty) {
    Board board;
    fillBoard(board);
    removeClues(board, cluesToRemoveForDifficulty(difficulty));
    board.lockFilledCells();
    return board;
}

}  // namespace sudoku
