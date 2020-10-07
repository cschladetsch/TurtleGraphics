// Copyright 2020 christian@schladetsch.com

#pragma once

namespace Turtle1 { namespace Processor {
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
}  // namespace Processor
}  // namespace Turtle1
