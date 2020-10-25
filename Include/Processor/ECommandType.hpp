// Copyright © 2020 christian@schladetsch.com

#pragma once

namespace TurtleGraphics::Processor {

enum class ECommandType {
    None,
    Value,
    PenDown,
    PenUp,
    Move,
    Rotate,
    Repeat,
    Function,
    Quit,
    Delta,
    X, Y, Z,
    Red, Green, Blue,
};

}  // namespace TurtleGraphics::Processor
