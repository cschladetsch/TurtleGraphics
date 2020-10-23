// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/RunContext.hpp"

namespace TurtleGraphics::Processor {

bool RunContext::Run() {
    if (!_lexer.Run(_code)) {
        Fail() << "Lexer: " << _lexer.GetError();
        return false;
    }

    if (!_parser.Run(_lexer)) {
        Fail() << "Parser: " << _parser.GetError();
        return false;
    }

    if (!_translator.Run(_parser.GetRoot())) {
        Fail() << "Translator: " << _translator.GetError();
        return false;
    }

    if (!_executor.Run(_translator.GetCommands())) {
        Fail() << "Exec: " << _executor.GetError();
        return false;
    }

    return true;
}

Scope &RunContext::GetScope() {
    return _executor.GetScope();
}

}   // namespace TurtleGraphics::Processor
