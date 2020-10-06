#pragma once

#include <string>

namespace T1 { namespace Processor {

    class Lexer;

    struct StringSplice {
        const Lexer* Source = 0;
        std::size_t LineNumber = 0;
        std::size_t Offset = 0;
        std::size_t Length = 0;

        StringSplice() { }

        StringSplice(const Lexer& lex, std::size_t ln, std::size_t ofs, std::size_t len)
            : Source(&lex) {
            LineNumber = ln;
            Offset = ofs;
            Length = len;
        }

        friend bool operator==(const StringSplice& left, const StringSplice& right) {
            return left.Source == right.Source && left.LineNumber == right.LineNumber && left.Offset == right.Offset && left.Length == right.Length;
        }

        std::string GetText() const;
    };
} }