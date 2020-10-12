// Copyright © 2020 christian@schladetsch.com

#pragma once

namespace TurtleGraphics::Processor {

enum class EToken {
    // virtual
    None,
    Start,
    StatementBlock,

    // real
    PenDown,
    PenUp,
    Function,
    ArgList,
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
    OpenParan,
    CloseParan,
    Comma,
};

}  // namespace TurtleGraphics::Processor
