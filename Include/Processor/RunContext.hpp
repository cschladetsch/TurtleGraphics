// Copyright © 2020 christian@schladetsch.com

#pragma once

#include "Processor/Lexer.hpp"
#include "Processor/Parser.hpp"
#include "Processor/Executor.hpp"

namespace Turtle1::Processor {

class RunContext : public ProcessBase
{
    Lexer _lexer;
    Parser _parser;
    Translator _translator;
    Executor _executor;

public:
    RunContext(Turtle &turtle, const char *code)
        : _lexer(code), _parser(_lexer), _translator(_parser.GetRoot()), _executor(turtle)
    {
    }

    bool Run() override;
};

}  // namespace Turtle1::Processor

