// Copyright 2020 christian@schladetsch.com

#pragma once

#include <variant>
#include "Config.hpp"

namespace Turtle1 { namespace Processor {

enum class ECommandType {
    None,
    Value,
    Move,
    Rotate,
    Repeat,
    Quit,
};

class CommandSequence;
typedef std::shared_ptr<CommandSequence> CommandSequencePtr;

struct Command {
    ECommandType Type;
    std::variant<int, string, CommandSequencePtr> Value;

    Command() : Command(ECommandType::None) {
    }

    explicit Command(ECommandType type) {
        Type = type;
    }

    explicit Command(string Text) : Command(ECommandType::Value) {
        Value = Text;
    }

    explicit Command(int num) : Command(ECommandType::Value) {
        Value = num;
    }
};

class CommandSequence {
    vector<Command> _commands;
    size_t _offset = 0;

public:
    CommandSequence(vector<Command> commands) {
        _commands = commands;
    }

    void Enter();
    void Leave();

    bool AtEnd() const { return _offset == _commands.size(); }
    Command Next();
};

}  // namespace Processor
}  // namespace Turtle1
