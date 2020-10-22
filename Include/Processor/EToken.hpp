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
    Repeat,
    If,
    Else,
    OpenBrace,
    CloseBrace,
    OpenParan,
    CloseParan,
    Comma,

    SetPositionComponent,
    DeltaPositionComponent,

    X, Y, Z,

    SetColor,
    SetColorByName,
    DeltaColorComponent,
    SetColorComponent,
    MulColorComponent,

    Red, Green, Blue, Alpha,

    Pink,
    Cyan,
    Black,
    White,
    Grey,
    Grey1,
    Grey2,
};

}  // namespace TurtleGraphics::Processor
