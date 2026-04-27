#include "input_handler.h"

#include <sstream>

namespace sudoku::cli {

Command InputHandler::parse(const std::string& input) {
    if (input.empty()) {
        return InvalidCommand{"Empty input. Type 'h' for help."};
    }

    std::istringstream stream(input);
    std::string token;
    stream >> token;

    if (token == "q" || token == "Q") {
        return QuitCommand{};
    }
    if (token == "u" || token == "U") {
        return UndoCommand{};
    }
    if (token == "s" || token == "S") {
        return SolveCommand{};
    }
    if (token == "n" || token == "N") {
        return NewGameCommand{};
    }
    if (token == "h" || token == "H") {
        return HelpCommand{};
    }

    int row = 0;
    int col = 0;
    int val = 0;

    try {
        row = std::stoi(token);
    } catch (...) {
        return InvalidCommand{"Unknown command. Type 'h' for help."};
    }

    if (!(stream >> col >> val)) {
        return InvalidCommand{"Expected: row col value (e.g. 3 5 7)"};
    }

    if (row < 1 || row > 9 || col < 1 || col > 9 || val < 1 || val > 9) {
        return InvalidCommand{"Row, column, and value must be between 1 and 9."};
    }

    return PlaceCommand{.row = row - 1, .col = col - 1, .value = val};
}

}  // namespace sudoku::cli
