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
    string fileName = "<in>";
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

    bool IsValid(StringSplice splice) const noexcept;

protected:
    friend class Parser;
    bool Fail(const char* errorText) const override ;
    std::ostream& Fail() const override;

private:
    void AddText(const char* text);
    void AddTokenNames();

    char GetCurrent() const noexcept;
    char GetAt(size_t offset) const;

    char Peek() const;
    bool AtEnd() const noexcept;
    bool AtEndAt(size_t offset) const noexcept;

    bool AddToken(StringSplice splice, EToken type);
    bool AddToken(EToken type, size_t length = 0);
    bool GetNext();

    StringSplice Gather(std::function<bool(char)> const& predicate) const;
    StringSplice GatherNumber() const;
};

}  // namespace TurtleGraphics::Processor
