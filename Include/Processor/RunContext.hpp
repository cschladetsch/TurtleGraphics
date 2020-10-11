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
    Turtle *_turtle = nullptr;
    const char* _code = nullptr;

public:
    RunContext(Turtle &turtle, const char *code)
        : _turtle(&turtle), _code(code)
    {
    }

    bool Run() noexcept override;

    Scope &GetScope();
};

}  // namespace Turtle1::Processor

