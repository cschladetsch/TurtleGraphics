// Copyright 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "Processor/ProcessBase.hpp"
#include "Processor/Token.hpp"
#include "Processor/StringSplice.hpp"

namespace T1 { namespace Processor {

// produces a series of Tokens from a string
class Lexer : public ProcessBase {
    std::vector<Token> _tokens;
    std::vector<std::string> _lines;
    std::size_t _lineNumber = 0;
    std::size_t _offset = 0;
    std::map<std::string, EToken> _tokenTypes;
    bool _failed;

 public:
    explicit Lexer(const char* text);

    bool Run() override;

    const std::vector<Token> GetTokens() const { return _tokens; }
    const std::vector<std::string>& GetLines() const { return _lines; }

    bool IsValid(StringSplice splice) const;

 private:
    void AddText(const char* text);
    void AddTokenNames();

    bool AtEnd() const;
    bool AtEnd(size_t offset) const;
    char GetCurrent() const;
    char GetCurrent(size_t offset) const;
    StringSplice Gather(std::function<bool(char)> predicate);
    bool AddToken(StringSplice splice, EToken type);
    bool AddToken(EToken type, size_t length);
    bool GetNext();
};
}  // namespace Processor
}  // namespace T1

