// Copyright 2020 christian@schladetsch.com

#pragma once

#include <variant>
#include "Config.hpp"
#include "Processor/ECommandType.hpp"

namespace Turtle1 { namespace Processor {

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

    explicit Command(CommandSequencePtr commands) : Command(ECommandType::Value) {
        Value = commands;
    }
};


}  // namespace Processor
}  // namespace Turtle1
