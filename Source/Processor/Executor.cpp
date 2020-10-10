// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Executor.hpp"
#include "Processor/CommandSequence.hpp"

namespace Turtle1::Processor {

Executor::Executor(Turtle& turtle, const CommandSequencePtr sequence)
    : _sequence((sequence)) {
    _turtle = &turtle;
    _context.push_back(sequence);
}

bool Executor::Run(CommandSequencePtr sequence) {
    _context.push_back(sequence);
    return NextSequence();
}

bool Executor::Run() {
    return NextSequence();
}

bool Executor::NextSequence() {
    if (_context.empty())
        return true;

    _commands = _context.back();
    _context.pop_back();
    return Execute(*_commands);
}

bool Executor::Execute(CommandSequence& sequence) {
    sequence.Enter();
    while (!sequence.AtEnd()) {
        Execute(sequence.Next());
        if (_break) {
            break;
        }
    }

    return NextSequence();
}

bool Executor::Execute(Command const &command) {
    switch (command.Type) {
    case ECommandType::PenUp:
        _turtle->PenDown = false;
        return true;
    case ECommandType::PenDown:
        _turtle->PenDown = true;
        return true;
    case ECommandType::Value:
        _data.push_back(command);
        return true;
    case ECommandType::Quit:
        _context.clear();
        _data.clear();
        _break = true;
        return true;
    case ECommandType::None:
        return true;
    case ECommandType::Move: {
        float distance = 0;
        if (!PopFloat(distance))
            return Fail("Distance expected");
        _turtle->Move(distance);
        return true;
    }
    case ECommandType::Rotate: {
        float angle = 0;
        if (!PopFloat(angle))
            return Fail("Angle expected");
        _turtle->Rotate(angle);
        return true;
    }
    case ECommandType::Repeat:
        return DoRepeat();
    }

    return Fail("Unhandled command");
}

bool Executor::PopFloat(float &num) {
    const auto opt = DataPop<int>();
    if (!opt.has_value())
        return Fail("No value");

    num = static_cast<float>(opt.value());
    return true;
}

bool Executor::DoRepeat() {
    auto numTimesOpt = DataPop<int>();
    if (!numTimesOpt.has_value()) {
        return Fail("Number of times to repeat expected");
    }

    auto commandsOpt = DataPop<CommandSequencePtr>();
    if (!commandsOpt.has_value()) {
        return Fail("Commands to repeat expected");
    }

    auto commands = *commandsOpt;
    for (auto n = 0; n < *numTimesOpt; ++n) {
        Run(commands);
        commands->Leave();
    }

    return true;
}

}  // namespace Turtle1::Processor
