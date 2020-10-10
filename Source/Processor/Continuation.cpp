// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Continuation.hpp"

namespace Turtle1::Processor {

Continuation::Continuation(vector<Command> commands)
    : _commands(std::move(commands)) {
}

bool Continuation::Run() noexcept {
    return false;
}

void Continuation::Reset() noexcept {
    _scope = _scopeEntered;
    _offset = 0;
}

bool Continuation::Enter(Executor &exec) {
    for (const auto &arg : _formalArgs) {
        auto opt = exec.PopData();
        if (!opt.has_value())
            return Fail("No arg for continuation");

        _scope[arg] = *opt;
    }

    _scopeEntered = _scope;
    return true;
}

void Continuation::Leave(Executor& exec) {
}

Command Continuation::Next() {
    if (AtEnd())
        return Command();

    return _commands[_offset++];
}

void Continuation::Append(const Command& cmd) {
    _commands.push_back(cmd);
}

}  // namespace Turtle1::Processor
