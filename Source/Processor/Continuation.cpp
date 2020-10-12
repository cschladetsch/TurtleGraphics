// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Continuation.hpp"

namespace TurtleGraphics::Processor {

Continuation::Continuation(vector<Command>&& commands, vector<Identifier>&& formalArgs)
    : _commands(std::move(commands))
    , _formalArgs(std::move(formalArgs)) {
}

bool Continuation::Run() noexcept {
    // Continuations cannot run themselves.
    return false;
}

void Continuation::Reset() noexcept {
    _offset = 0;
    _scope = _enteredScope;
}

bool Continuation::Enter(Executor& exec) {
    for (const auto& arg : _formalArgs) {
        auto opt = exec.PopData();
        if (!opt.has_value()) {
            return Fail("Missing argument for continuation");
        }

        _scope[arg] = *opt;
    }

    _enteredScope = _scope;
    _offset = 0;
    return true;
}

Command Continuation::Next() {
    if (AtEnd()) {
        //Warn("At end of continuation");
        return Command();
    }

    return _commands[_offset++];
}

void Continuation::Append(const Command& command) {
    _commands.push_back(command);
}

}  // namespace TurtleGraphics::Processor

