// Copyright © 2020 christian@schladetsch.com

#pragma once

#include "Config.hpp"
#include "Processor/Command.hpp"

namespace Turtle1::Processor {

class CommandSequence {
    vector<Command> _commands;
    size_t _offset = 0;

public:
    CommandSequence() = default;
    explicit CommandSequence(vector<Command> commands);

    void Reset();
    void Enter();
    void Leave();

    [[nodiscard]] bool AtEnd() const { return _offset == _commands.size(); }
    [[nodiscard]] Command Next();

private:
    friend class Translator;

    void Append(const Command& command);
};

}  // namespace Turtle1::Processor

