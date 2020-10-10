// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>

#include "StdAliases.hpp"

namespace Turtle1 { namespace Processor {

class Lexer;

struct StringSplice {
    const Lexer* Source = 0;
    size_t LineNumber = 0;
    size_t Offset = 0;
    size_t Length = 0;

    StringSplice() { }

    StringSplice(const Lexer& lex, std::size_t ln,
        size_t ofs, size_t len)
        : Source(&lex) {
        LineNumber = ln;
        Offset = ofs;
        Length = len;
    }

    friend bool operator==(const StringSplice& left,
        const StringSplice& right) {
        return left.Source == right.Source
            && left.LineNumber == right.LineNumber
            && left.Offset == right.Offset
            && left.Length == right.Length;
    }

    string GetText() const;
};
}  // namespace Processor
}  // namespace Turtle1
