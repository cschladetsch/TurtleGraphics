#pragma once

#include <string>

namespace T1 {
    namespace Processor {

        class Lexer;

        struct StringSplice
        {
            const Lexer* Source = 0;
            int LineNumber = 0;
            int Offset = 0;
            int Length = 0;

            StringSplice() { }

            StringSplice(const Lexer& lex, int ln, int ofs, int len)
                : Source(&lex)
            {
                LineNumber = ln;
                Offset = ofs;
                Length = len;
            }

            friend bool operator==(const StringSplice& left, const StringSplice& right)
            {
                return left.Source == right.Source && left.LineNumber == right.LineNumber && left.Offset == right.Offset && left.Length == right.Length;
            }

            std::string GetText() const;
        };
    }
}