// Copyright � 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Lexer.hpp"

namespace TurtleGraphics::Processor {

std::string StringSplice::GetText() const {
    assert(Source != nullptr);
    assert(Source->IsValid(*this));

    return Source->GetLines()[LineNumber].substr(Offset, Length);
}

Lexer::Lexer() {
    AddTokenNames();
}
Lexer::Lexer(const char* code) : Lexer() {
    AddText(code);
}

bool Lexer::Run(const char* code) noexcept {
    AddText(code);
    return Run();
}

bool Lexer::IsValid(const StringSplice splice) const {
    if (splice.LineNumber >= _lines.size())
        return false;

    auto const& line = _lines[splice.LineNumber];
    return splice.Offset < line.size()
        && splice.Offset + splice.Length < line.size();
}

void Lexer::AddTokenNames() {
    _tokenTypes["penDown"] = EToken::PenDown;
    _tokenTypes["penUp"] = EToken::PenUp;
    _tokenTypes["move"] = EToken::Move;
    _tokenTypes["rotate"] = EToken::Rotate;
    _tokenTypes["quit"] = EToken::Quit;
    _tokenTypes["color"] = EToken::Color;
    _tokenTypes["true"] = EToken::True;
    _tokenTypes["false"] = EToken::False;
    _tokenTypes["repeat"] = EToken::Repeat;
    _tokenTypes["if"] = EToken::If;
    _tokenTypes["else"] = EToken::Else;
    _tokenTypes["fun"] = EToken::Function;
}

void Lexer::AddText(const char *text) {
    assert(text != nullptr);

    const char* start = text;
    while (text && *text) {
        const auto ch = *text;
        if (ch == '\n') {
            _lines.push_back(std::string(start, text + 1));
            start = text + 1;
        }

        ++text;
    }

    _lines.push_back(std::string(start, text + 1));
}

bool Lexer::Run() noexcept {
    Reset();

    while (GetNext()) {
    }

    return !_failed;
}

bool Lexer::GetNext() {
    if (AtEnd())
        return false;

    const auto current = GetCurrent();
    if (current == '\n') {
        _lineNumber++;
        return true;
    }

    if (std::isalpha(current)) {
        const auto splice = Gather(std::isalpha);
        const auto text = splice.GetText();
        const auto tokenType = _tokenTypes.find(text);
        if (tokenType != _tokenTypes.end())
            return AddToken(splice, tokenType->second);

        return AddToken(splice, EToken::Identifier);
    }

    if (std::isdigit(current))
        return AddToken(Gather(std::isdigit), EToken::Number);

    if (std::isspace(current))
        return AddToken(Gather(std::isspace), EToken::WhiteSpace);

    switch (current) {
    case '{': return AddToken(EToken::OpenBrace, 1);
    case '}': return AddToken(EToken::CloseBrace, 1);
    case '(': return AddToken(EToken::OpenParan, 1);
    case ')': return AddToken(EToken::CloseParan, 1);
    case ',': return AddToken(EToken::Comma, 1);
    default: ;
    }

    // TODO(cjs): error reporting
    _failed = current != 0;
    if (!_failed)
        _tokens.emplace_back(Token{ EToken::None });

    return false;
}

bool Lexer::AddToken(EToken type, size_t length) {
    return AddToken(
        StringSplice(*this, _lineNumber, _offset, length), type);
}

bool Lexer::AddToken(StringSplice const splice, EToken type) {
    _tokens.emplace_back(Token{ type, splice });
    _offset += splice.Length;
    return true;
}

StringSplice Lexer::Gather(std::function<bool(char)> predicate) const
{
    auto end = _offset;
    while (!AtEnd(end) && predicate(GetCurrent(end)))
        ++end;

    return { *this, _lineNumber, _offset, end - _offset };
}

bool Lexer::AtEnd(size_t offset) const {
    if (_lineNumber == _lines.size())
        return false;

    return offset >= _lines[_lineNumber].size();
}

bool Lexer::AtEnd() const {
    return AtEnd(_offset);
}

char Lexer::GetCurrent(size_t offset) const {
    if (AtEnd(offset))
        return 0;

    return _lines[_lineNumber][offset];
}

char Lexer::GetCurrent() const {
    return GetCurrent(_offset);
}

}  // namespace TurtleGraphics::Processor

