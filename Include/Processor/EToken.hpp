// Copyright © 2020 christian@schladetsch.com

#pragma once

namespace TurtleGraphics::Processor {

enum class EToken {
    // virtual
    None,
    Start,
    StatementBlock,

    // real
    True,
    False,
    Number,
    Identifier,

    PenDown,
    PenUp,
    Function,
    OpenParan,
    CloseParan,
    ArgList,
    Comma,
    OpenBrace,
    CloseBrace,

    Move,
    Rotate,
    RotateX,
    RotateY,
    RotateZ,

    WhiteSpace,
    Quit,

    Repeat,
    If,
    Else,
    While,

    SetPositionComponent,
    DeltaPositionComponent,

    X, Y, Z,

    SetColor,
    SetColorByName,  // color names set in config file
    Delta,
    SetColorComponent,
    MulColorComponent,

    Red, Green, Blue, Alpha,
};

}  // namespace TurtleGraphics::Processor
