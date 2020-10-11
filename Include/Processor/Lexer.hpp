// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "Processor/ProcessBase.hpp"
#include "Processor/Token.hpp"
#include "Processor/StringSplice.hpp"

namespace Turtle1::Processor {

class Lexer : public ProcessBase {
    vector<Token> _tokens;
    vector<string> _lines;
    size_t _lineNumber = 0;
    size_t _offset = 0;
    map<string, EToken> _tokenTypes;

public:
    Lexer();
    explicit Lexer(const char* code);

    bool Run(const char* code) noexcept;
    bool Run() noexcept override;

    const vector<Token>& GetTokens() const { return _tokens; }
    const vector<string>& GetLines() const { return _lines; }

    bool IsValid(StringSplice splice) const;

private:
    void AddText(const char* text);
    void AddTokenNames();

    bool AtEnd() const;
    bool AtEnd(size_t offset) const;
    char GetCurrent() const;
    char GetCurrent(size_t offset) const;
    StringSplice Gather(std::function<bool(char)> predicate) const;
    bool AddToken(StringSplice splice, EToken type);
    bool AddToken(EToken type, size_t length);
    bool GetNext();
};

}  // namespace Turtle1::Processor
