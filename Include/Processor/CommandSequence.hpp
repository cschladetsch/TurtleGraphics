// Copyright 2020 christian@schladetsch.com

#pragma once

#include "Config.hpp"
#include "Processor/Command.hpp"

namespace Turtle1 { namespace Processor {
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
