#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "Pch.hpp"
#include <algorithm>
#include <array>

#include "Processor/Lexer.hpp"
#include "Processor/Parser.hpp"

using namespace T1::Processor;

TEST_CASE("Test String", "[processor]")
{
    const char* text = "hello\nworld";
    std::string hello(text, text + 6);
    REQUIRE(hello[5] == '\n');
}

TEST_CASE("Test Lexer", "[processor]")
{
    const char* i0 = "penDown  move\t50 repeat 123 quit";
    Lexer lexer(i0);

    std::array expected
    {
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
    REQUIRE(std::equal(begin(tokens), end(tokens), begin(expected)));
}

TEST_CASE("Test Parser", "[processor]")
{
    const char* i0 = "penDown repeat 4 { rotate 90 move 100 } quit";
    Lexer lexer(i0);
    REQUIRE(lexer.Run());

    Parser parser(lexer);

    REQUIRE(parser.Run());
    auto root = parser.GetRoot();
    REQUIRE(root);

    auto const& children = root->GetChildren();
    REQUIRE(children.size() == 3);
    REQUIRE(children[0]->GetType() == PenDown);
    REQUIRE(children[1]->GetType() == Repeat);
    REQUIRE(children[2]->GetType() == Quit);

    auto repeat = children[1];
    auto repeatChildren = repeat->GetChildren();
    REQUIRE(repeatChildren.size() == 3);
    REQUIRE(repeatChildren[0]->GetType() == Number);
    REQUIRE(repeatChildren[1]->GetType() == Rotate);
    REQUIRE(repeatChildren[2]->GetType() == Move);

    // rotate command
    REQUIRE(repeatChildren[1]->GetChildren().size() == 1);

    // move command
    REQUIRE(repeatChildren[2]->GetChildren().size() == 1);

    REQUIRE(repeatChildren[1]->GetChildren()[0]->GetType() == Number);
    REQUIRE(repeatChildren[2]->GetChildren()[0]->GetType() == Number);

}
