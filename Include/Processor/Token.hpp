// Copyright © 2020 christian@schladetsch.com

#pragma once

#include "Processor/EToken.hpp"
#include "Processor/StringSplice.hpp"

namespace TurtleGraphics::Processor {

struct Token {
    EToken Type;
    StringSplice Splice;

    explicit Token(EToken type = EToken::None) noexcept : Type(type) { }

    Token(EToken type, const StringSplice splice) noexcept : Token(type) {
        Splice = splice;
    }

    friend bool operator==(const Token& left, const Token& right) {
        return left.Type == right.Type;
    }
};

}  // namespace TurtleGraphics::Processor

