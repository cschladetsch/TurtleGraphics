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
    SetColorByName, // color names set in config file
    DeltaColorComponent,
    SetColorComponent,
    MulColorComponent,

    Red, Green, Blue, Alpha,

    // deal with these dynamically via config file
    //Black,
    //White,
    //Pink,
    //Cyan,
    //Purple,
    //Grey,
    //Grey1,
    //Grey2,
};

}  // namespace TurtleGraphics::Processor
