#pragma once

#include <string>
#include <vector>

#include "Processor/Token.hpp"
#include "Processor/StringSplice.hpp"

namespace T1 { namespace Processor {

    class Lexer;

    // produces a series of Tokens from a string
    class Lexer
    {
        std::vector<Token> _tokens;

    public:
        explicit Lexer(const char* text);

        bool Run();

        const std::vector<Token> GetTokens() const { return _tokens; }
    };
}}

