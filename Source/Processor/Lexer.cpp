// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Lexer.hpp"

namespace TurtleGraphics::Processor {

std::string StringSplice::GetText() const {
    assert(Source != nullptr);
    assert(Source->IsValid(*this));

    return Source->GetLines()[LineNumber].substr(Offset, Length);
}

Lexer::Lexer()
{
    AddTokenNames();
}
Lexer::Lexer(const char* code) : Lexer() {
    AddText(code);
}

bool Lexer::Run(const char* code) {
    AddText(code);
    return Run();
}

bool Lexer::IsValid(const StringSplice splice) const noexcept {
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
    _tokenTypes["color"] = EToken::SetColor;
    _tokenTypes["colorName"] = EToken::SetColorByName;
    _tokenTypes["colorComponent"] = EToken::SetColorComponent;
    _tokenTypes["mulColorComponent"] = EToken::MulColorComponent;
    _tokenTypes["true"] = EToken::True;
    _tokenTypes["false"] = EToken::False;
    _tokenTypes["repeat"] = EToken::Repeat;
    _tokenTypes["if"] = EToken::If;
    _tokenTypes["else"] = EToken::Else;
    _tokenTypes["fun"] = EToken::Function;
    _tokenTypes["X"] = EToken::X;
    _tokenTypes["Y"] = EToken::Y;
    _tokenTypes["Z"] = EToken::Z;
    _tokenTypes["Red"] = EToken::Red;
    _tokenTypes["Green"] = EToken::Green;
    _tokenTypes["Blue"] = EToken::Blue;
    _tokenTypes["Alpha"] = EToken::Alpha;
}

void Lexer::AddText(const char *text) {
    assert(text != nullptr);

    const auto* start = text;
    while (text && *text) {
        const auto ch = *text;
        if (ch == '\n') {
            _lines.push_back(std::string(start, text + 1));
            start = text + 1;
        }

        ++text;
    }

    auto line = std::string(start, text);
    if (line.empty() || line.back() != '\n')
        line.push_back('\n');

    _lines.push_back(line);
}

bool Lexer::Run() {
    Reset();

    while (GetNext()) {
    }

    return !_failed;
}

bool Lexer::GetNext() {
    if (AtEnd()) {
        AddToken(EToken::None);
        return false;
    }

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
    if (!_failed)
        _tokens.emplace_back(Token{ EToken::None });

    return false;
}

bool Lexer::AddToken(EToken type, size_t length) {
    return AddToken(
        StringSplice(*this, _lineNumber, _offset, length), type);
}

bool Lexer::AddToken(StringSplice const splice, EToken type) {
    try {
        _tokens.emplace_back(Token{ type, splice });
    } catch (std::exception &e) {
        return Fail(e.what());
    }

    _offset += splice.Length;
    return true;
}

StringSplice Lexer::Gather(std::function<bool(char)> const& predicate) const {
    auto end = _offset;
    while (!AtEnd(end) && predicate(GetCurrent(end)))
        ++end;

    return { *this, _lineNumber, _offset, end - _offset };
}

bool Lexer::AtEnd(size_t offset) const noexcept {
    if (_lineNumber >= _lines.size())
        return true;

    return offset >= _lines[_lineNumber].size();
}

bool Lexer::AtEnd() const noexcept {
    return AtEnd(_offset);
}

char Lexer::GetCurrent(size_t offset) const {
    if (AtEnd(offset))
        return 0;

    return _lines[_lineNumber][offset];
}

char Lexer::GetCurrent() const noexcept {
    return GetCurrent(_offset);
}

}  // namespace TurtleGraphics::Processor

