#include <algorithm>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Processor/Lexer.hpp"

using namespace T1::Processor;

TEST_CASE("Test Lexer", "[processor]")
{
    const char* i0 = "P true\nM 50\n";
    Lexer lexer(i0);
    const auto tokens = lexer.GetTokens();
    EToken expected[] =
    {
        EToken::PenChange,
        EToken::WhiteSpace,
        EToken::True,
        EToken::WhiteSpace,
        EToken::Move,
        EToken::WhiteSpace,
        EToken::Number,
        EToken::WhiteSpace,
        EToken::None,
    };

    REQUIRE(lexer.Run());
    REQUIRE(tokens.size() == 9);
    REQUIRE(std::equal(begin(tokens), end(tokens), expected));
}

