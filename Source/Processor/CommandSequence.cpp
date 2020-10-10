// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/CommandSequence.hpp"

namespace Turtle1::Processor {

CommandSequence::CommandSequence(const vector<Command> &commands)
    : _commands(commands)
{
}

void CommandSequence::Enter() {
}

void CommandSequence::Leave() {
    _offset = 0;
}

Command CommandSequence::Next() {
    if (AtEnd())
        return Command();

    return _commands[_offset++];
}

}  // namespace Turtle1::Processor
