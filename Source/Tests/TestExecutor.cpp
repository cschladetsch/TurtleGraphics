// Copyright © 2020 christian@schladetsch.com
#ifdef TURTLE_UNIT_TESTS

#include <array>

#include "catch.hpp"

#include "Turtle.hpp"
#include "Color.hpp"
#include "Processor/Lexer.hpp"
#include "Processor/Parser.hpp"
#include "Processor/Translator.hpp"
#include "Processor/Continuation.hpp"
#include "Processor/Executor.hpp"
#include "Processor/RunContext.hpp"

using TurtleGraphics::Turtle;
using TurtleGraphics::Position;
using TurtleGraphics::Color;
using TurtleGraphics::ColorInt;

using TurtleGraphics::Processor::EToken;
using TurtleGraphics::Processor::Lexer;
using TurtleGraphics::Processor::Parser;
using TurtleGraphics::Processor::Translator;
using TurtleGraphics::Processor::Executor;
using TurtleGraphics::Processor::Command;
using TurtleGraphics::Processor::ECommandType;
using TurtleGraphics::Processor::Continuation;
using TurtleGraphics::Processor::RunContext;

static Turtle Execute(const char* text)
{
    Turtle turtle;
    RunContext context(turtle, text);
    REQUIRE(context.Run());
    turtle.Location = turtle.Process();
    return turtle;
}

TEST_CASE("Test Empty String", "[processor]") {
    Execute("");
}

TEST_CASE("Test Empty String With NL", "[processor]") {
    Execute("\n");
}

TEST_CASE("Test Move 1", "[processor]") {
    auto t = Execute("move 1");
    REQUIRE(t.Location == Position(501, 500));
}

TEST_CASE("Test Move 1 NL", "[processor]") {
    auto t = Execute("move 1\n");
    REQUIRE(t.Location == Position(501, 500));
}

#endif
