#pragma once

#include "Processor/Lexer.hpp"

namespace T1 { namespace Processor {
    // produces an AST from a series of tokens
    class Parser
    {
        const Lexer& _lexer;

    public:
        Parser(const Lexer& lexer);


    };
} }
