// Copyright © 2020 christian@schladetsch.com

#pragma once

#include "Processor/Lexer.hpp"
#include "Processor/Parser.hpp"
#include "Processor/Translator.hpp"
#include "Processor/Executor.hpp"

namespace TurtleGraphics::Processor {

class RunContext : public ProcessBase {
    Lexer _lexer;
    Parser _parser;
    Translator _translator;
    Executor _executor;
    const char* _code = nullptr;

public:
    RunContext(Turtle &turtle, const char *code)
        : _executor(turtle), _code(code) {
    }

    bool Run() override;
    Scope &GetScope();
};

}  // namespace TurtleGraphics::Processor

