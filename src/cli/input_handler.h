#pragma once

#include <string>
#include <variant>

namespace sudoku::cli {

struct PlaceCommand {
    int row;
    int col;
    int value;
};

struct UndoCommand {};
struct SolveCommand {};
struct NewGameCommand {};
struct HelpCommand {};
struct QuitCommand {};
struct InvalidCommand {
    std::string reason;
};

using Command = std::variant<PlaceCommand, UndoCommand, SolveCommand, NewGameCommand, HelpCommand,
                             QuitCommand, InvalidCommand>;

/// Parses raw user input into a typed Command.
class InputHandler {
public:
    [[nodiscard]] static Command parse(const std::string& input);
};

}  // namespace sudoku::cli
