// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "Processor/ProcessBase.hpp"
#include "Processor/Token.hpp"
#include "Processor/StringSplice.hpp"

namespace TurtleGraphics::Processor {

class Lexer : public ProcessBase {
    vector<Token> _tokens;
    vector<string> _lines;
    size_t _lineNumber = 0;
    size_t _offset = 0;
    map<string, EToken> _tokenTypes;

public:
    Lexer() noexcept;
    explicit Lexer(const char* code);

    bool Run(const char* code);
    bool Run() override;

    const vector<Token>& GetTokens() const noexcept { return _tokens; }
    const vector<string>& GetLines() const noexcept { return _lines; }

    [[nodiscard]] bool IsValid(StringSplice splice) const noexcept;

private:
    void AddText(const char* text);
    void AddTokenNames();

    bool AtEnd() const noexcept;
    bool AtEnd(size_t offset) const noexcept;
    char GetCurrent() const noexcept;
    char GetCurrent(size_t offset) const;
    StringSplice Gather(std::function<bool(char)> const& predicate) const;
    bool AddToken(StringSplice splice, EToken type);
    bool AddToken(EToken type, size_t length = 0);
    bool GetNext();
};

}  // namespace TurtleGraphics::Processor
