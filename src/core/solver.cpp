#include <sudoku/solver.h>
#include <sudoku/validator.h>

namespace sudoku {

namespace {

bool solveRecursive(Board& board) {
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (!board.isEmpty(r, c)) {
                continue;
            }

            for (int v = 1; v <= kBoardSize; ++v) {
                if (Validator::isValidPlacement(board, r, c, v)) {
                    board.setCell(r, c, v);
                    if (solveRecursive(board)) {
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

/// Count solutions up to a limit to test uniqueness without exhaustive search.
int countSolutions(Board& board, int limit) {
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if (!board.isEmpty(r, c)) {
                continue;
            }

            int count = 0;
            for (int v = 1; v <= kBoardSize; ++v) {
                if (Validator::isValidPlacement(board, r, c, v)) {
                    board.setCell(r, c, v);
                    count += countSolutions(board, limit - count);
                    board.clearCell(r, c);
                    if (count >= limit) {
                        return count;
                    }
                }
            }
            return count;
        }
    }
    return 1;
}

}  // namespace

bool Solver::solve(Board& board) {
    return solveRecursive(board);
}

std::optional<Board> Solver::solved(const Board& board) {
    Board copy = board;
    if (solveRecursive(copy)) {
        return copy;
    }
    return std::nullopt;
}

bool Solver::hasUniqueSolution(const Board& board) {
    Board copy = board;
    return countSolutions(copy, 2) == 1;
}

}  // namespace sudoku
