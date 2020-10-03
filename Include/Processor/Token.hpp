#pragma once

#include "Processor/StringSplice.hpp"

namespace T1 {
    namespace Processor {
        enum EToken
        {
            None,
            PenChange,
            True,
            False,
            Move,
            Rotate,
            WhiteSpace,
            Number,
        };

        struct Token
        {
            EToken Type;
            StringSplice Splice;

            Token(EToken type = EToken::None) : Type(type) { }
            Token(EToken type, StringSplice splice) : Token(type)
            {
                Splice = splice;
            }

            friend bool operator==(const Token& left, const Token& right)
            {
                return left.Type == right.Type && left.Splice == right.Splice;
            }
        };
    }
}

