// Copyright © 2020 christian@schladetsch.com

#pragma once

#include "Processor/Lexer.hpp"
#include "Processor/Parser.hpp"
#include "Processor/Executor.hpp"

namespace Turtle1::Processor {

class RunContext final : public ProcessBase
{
    Lexer _lexer;
    Parser _parser;
    Translator _translator;
    Executor _executor;

public:
    bool Run(const char *text);
    bool Run() override;

private:
    RunContext() = delete;
};

}  // namespace Turtle1::Processor

