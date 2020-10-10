// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <variant>
#include "Processor/ECommandType.hpp"

namespace Turtle1 { namespace Processor {

class CommandSequence;
typedef std::shared_ptr<CommandSequence> CommandSequencePtr;

struct Command {
    ECommandType Type;
    std::variant<int, string, CommandSequencePtr> Value;

    Command() : Command(ECommandType::None) {
    }

    explicit Command(const ECommandType type) {
        Type = type;
    }

    explicit Command(const string& text) : Value(text) {
        Type = ECommandType::Value;
    }

    explicit Command(int num) : Command(ECommandType::Value) {
        Value = num;
    }

    explicit Command(const CommandSequencePtr& commands) : Value(commands) {
        Type = ECommandType::Value;
    }
};


}  // namespace Processor
}  // namespace Turtle1
