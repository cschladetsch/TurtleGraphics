// Copyright 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Executor.hpp"
#include "Processor/CommandSequence.hpp"

namespace Turtle1 { namespace Processor {
    
void Executor::Run(CommandSequencePtr sequence) {
    _context.push_back(sequence);
    NextSequence();
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

bool Executor::Execute(Command command) {
    switch (command.Type) {
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

bool Executor::PopFloat(float &f) {
    auto val = DataPop<int>();
    if (!val.has_value()) {
        return Fail("No value");
    }
    f = static_cast<float>(val.value());
    return true;
}

bool Executor::DoRepeat() {
    return Fail("Not implemented");
}

}  // namespace Processor
}  // namespace Turtle1
