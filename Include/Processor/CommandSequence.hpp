// Copyright 2020 christian@schladetsch.com

#pragma once

#include "Config.hpp"
#include "Processor/Command.hpp"

namespace Turtle1 { namespace Processor {
class CommandSequence {
    vector<Command> _commands;
    size_t _offset = 0;

public:
    CommandSequence() { }
    CommandSequence(vector<Command> commands) {
        _commands = commands;
    }

    void Enter();
    void Leave();

    bool AtEnd() const { return _offset == _commands.size(); }
    Command Next();

private:
    friend class Translator;

    void Append(Command cmd) {
        _commands.push_back(cmd);
    }
};
}  // namespace Processor
}  // namespace Turtle1
