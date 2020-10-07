// Copyright 2020 christian@schladetsch.com

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <algorithm>
#include <array>

#include "Turtle.hpp"
#include "Processor/Lexer.hpp"
#include "Processor/Parser.hpp"
#include "Processor/Translator.hpp"
#include "Processor/Executor.hpp"

using Turtle1::Turtle;

using Turtle1::Processor::EToken;
using Turtle1::Processor::Token;
using Turtle1::Processor::Lexer;
using Turtle1::Processor::Parser;
using Turtle1::Processor::Translator;
using Turtle1::Processor::Executor;
using Turtle1::Processor::Command;
using Turtle1::Processor::ECommandType;
using Turtle1::Processor::CommandSequence;

TEST_CASE("Test String", "[processor]") {
    const char* text = "hello\nworld";
    std::string hello(text, text + 6);
    REQUIRE(hello[5] == '\n');
}

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
    Turtle turtle;
    auto commands = std::vector { 
        Command(50),
        Command(ECommandType::Rotate),
        Command(100),
        Command(ECommandType::Move),
    };
    auto sequence = std::make_shared<CommandSequence>(commands);

    Executor executor{ turtle, sequence };
    REQUIRE(executor.Run());

    REQUIRE(true);
}


