// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/CommandSequence.hpp"

namespace Turtle1::Processor {

CommandSequence::CommandSequence(vector<Command> commands)
    : _commands(std::move(commands))
{
}

void CommandSequence::Reset() {
    _offset = 0;
}

void CommandSequence::Enter() {
}

void CommandSequence::Leave() {
}

Command CommandSequence::Next() {
    if (AtEnd())
        return Command();

    return _commands[_offset++];
}

void CommandSequence::Append(const Command& cmd) {
    _commands.push_back(cmd);
}

}  // namespace Turtle1::Processor
