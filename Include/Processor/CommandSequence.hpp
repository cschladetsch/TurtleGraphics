// Copyright © 2020 christian@schladetsch.com

#pragma once

#include "Config.hpp"
#include "Processor/Command.hpp"

namespace Turtle1 { namespace Processor {
class CommandSequence {
    vector<Command> _commands;
    size_t _offset = 0;

public:
    CommandSequence() { }

    explicit CommandSequence(const vector<Command> &commands);

    static void Enter();
    void Leave();

    [[nodiscard]] bool AtEnd() const { return _offset == _commands.size(); }
    Command Next();

private:
    friend class Translator;

    void Append(const Command cmd) {
        _commands.push_back(cmd);
    }
};
}  // namespace Processor
}  // namespace Turtle1
