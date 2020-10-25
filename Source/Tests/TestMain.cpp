// Copyright © 2020 christian@schladetsch.com
#ifdef TURTLE_UNIT_TESTS

#define CATCH_CONFIG_MAIN

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

TEST_CASE("Test Lexer", "[processor]") {
    const char* i0 = "penDown  move\t50 repeat 123 quit";
    Lexer lexer(i0);

    std::array expected {
        EToken::PenDown,
        EToken::WhiteSpace,
        EToken::Move,
        EToken::WhiteSpace,
        EToken::Number,
        EToken::WhiteSpace,
        EToken::Repeat,
        EToken::WhiteSpace,
        EToken::Number,
        EToken::WhiteSpace,
        EToken::Quit,
        EToken::None,
    };

    REQUIRE(lexer.Run());
    const auto tokens = lexer.GetTokens();
    REQUIRE(tokens.size() == expected.size());
// TODO(cjs): REQUIRE(std::equal(begin(tokens), end(tokens), begin(expected)));
}

TEST_CASE("Test String", "[processor]") {
    const char* text = "hello\nworld";
    std::string hello(text, text + 6);
    REQUIRE(hello[5] == '\n');
}

float ToNumber(Lexer const &lexer) {
    return static_cast<float>(
        atof(lexer.GetTokens().at(0).Splice.GetText().c_str()));
}

TEST_CASE("Test Lexer Number", "[lexer]") {
    Lexer l0("0");
    Lexer l1("-0");
    Lexer l2("+0");
    Lexer l3("-0.123");
    Lexer l5("+0.123");
    Lexer l4("0.123");

    l0.Run();
    l1.Run();
    l2.Run();
    l3.Run();
    l4.Run();
    l5.Run();

    REQUIRE(ToNumber(l0) == 0);
    REQUIRE(ToNumber(l1) == 0);
    REQUIRE(ToNumber(l2) == 0);
    REQUIRE(ToNumber(l3) == -0.123f);
    REQUIRE(ToNumber(l4) == 0.123f);
    REQUIRE(ToNumber(l5) == 0.123f);
}

TEST_CASE("Test Lexer Number with Exponents", "[lexer]") {
    //Lexer l6("+0.1e-1");
    //Lexer l7("+0.1e+12");
    //l6.Run();
    //l7.Run();
    //REQUIRE(ToNumber(l6) == 0.1e-1);
    //REQUIRE(ToNumber(l7) == 0.1e+12);
}


TEST_CASE("Test Parser", "[processor]") {
    const char* i0 = "penDown repeat 4 { rotate 90 move 100 } quit";
    Lexer lexer(i0);
    REQUIRE(lexer.Run());

    Parser parser(lexer);

    REQUIRE(parser.Run());
    auto root = parser.GetRoot();
    REQUIRE(root);

    auto const& children = root->GetChildren();
    REQUIRE(children.size() == 3);
    REQUIRE(children[0]->GetType() == EToken::PenDown);
    REQUIRE(children[1]->GetType() == EToken::Repeat);
    REQUIRE(children[2]->GetType() == EToken::Quit);

    auto repeat = children[1];
    auto repeatChildren = repeat->GetChildren();
    REQUIRE(repeatChildren.size() == 3);
    REQUIRE(repeatChildren[0]->GetType() == EToken::Number);
    REQUIRE(repeatChildren[1]->GetType() == EToken::Rotate);
    REQUIRE(repeatChildren[2]->GetType() == EToken::Move);

    // rotate command
    REQUIRE(repeatChildren[1]->GetChildren().size() == 1);

    // move command
    REQUIRE(repeatChildren[2]->GetChildren().size() == 1);

    auto rotateValue = repeatChildren[1]->GetChildren()[0];
    auto moveValue = repeatChildren[2]->GetChildren()[0];
    REQUIRE(std::stoi(rotateValue->GetText()) == 90);
    REQUIRE(std::stoi(moveValue->GetText()) == 100);
}

TEST_CASE("Test Executor", "[exec]") {
    TurtleGraphics::Turtle turtle;
    auto commands = std::vector { 
        Command(50),
        Command(ECommandType::Rotate),
        Command(100),
        Command(ECommandType::Move),
    };
    auto sequence = std::make_shared<Continuation>(commands);

    Executor executor{ turtle, sequence };
    REQUIRE(executor.Run());

    REQUIRE(true);
}

TEST_CASE("Test Whitespace in Parser", "[exec]") {
    const char* i0 = "penDown repeat 4\n{\trotate 80\n\tmove 120\n}\n";
    Lexer lexer(i0);
    REQUIRE(lexer.Run());

    Parser parser(lexer);
    REQUIRE(parser.Run());

    Translator translator(parser.GetRoot());
    REQUIRE(translator.Run());

    Turtle turtle;
    Executor exec(turtle, translator.GetCommands());
    REQUIRE(exec.Run());
}

TEST_CASE("Test RunContext", "[exec]") {
    Turtle turtle;
    RunContext context(turtle, "move 100");
    REQUIRE(context.Run());
}

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

TEST_CASE("Test Color", "[prims]") {
    Color a(0, 0, 0);
    REQUIRE(a.Normalise() == Color(0, 0, 0));

    Color b(-4.75f, 0, 0);
    REQUIRE(b.Normalise() == Color(0.25f, 0, 0));

    Color c(1.75f, 0, 0);
    REQUIRE(c.Normalise() == Color(0.75f, 0, 0));

    ColorInt v(c);
    REQUIRE(v == ColorInt(static_cast<int>(0.75f * 255), 0, 0));
}

TEST_CASE("Test Delta color", "[exec]") {
    const char* code = "delta red -25";
    Turtle turtle;
    RunContext context(turtle, code);
    context.Run();
    std::cout << context.GetError().c_str();
    REQUIRE(context.HasSucceeded());

    //REQUIRE(turtle.Color == Color(0.75f, 0, 0));
}

TEST_CASE("Test Function decl", "[exec][function]") {
    Turtle turtle;
    RunContext context(turtle, "fun foo(a){}");
    REQUIRE(context.Run());
    //REQUIRE(context.GetScope().contains("foo"));
}

TEST_CASE("Test Function impl", "[exec][function]") {
    Turtle turtle;
    TurtleGraphics::Processor::RunContext context(turtle, "fun foo(a){ move a }");
    //REQUIRE(context.Run());
    //REQUIRE(context.GetScope().contains("foo"));
}


#endif // TURTLE_UNIT_TESTS
