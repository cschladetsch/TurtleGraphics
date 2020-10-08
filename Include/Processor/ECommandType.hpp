// Copyright 2020 christian@schladetsch.com

#pragma once

namespace Turtle1 { namespace Processor {
enum class ECommandType {
    None,
    Value,
    PenDown,
    PenUp,
    Move,
    Rotate,
    Repeat,
    Quit,
};
}  // namespace Processor
}  // namespace Turtle1