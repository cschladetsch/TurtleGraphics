// Copyright © 2020 christian@schladetsch.com

#pragma once

namespace Turtle1::Processor {

enum class EToken {
    None,
    Start,
    PenDown,
    PenUp,
    True,
    False,
    Move,
    Rotate,
    WhiteSpace,
    Number,
    Identifier,
    Quit,
    Color,
    Repeat,
    If,
    Else,
    OpenBrace,
    CloseBrace,
};

}  // namespace Turtle1::Processor
