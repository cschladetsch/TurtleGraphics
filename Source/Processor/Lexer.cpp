// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Lexer.hpp"

namespace TurtleGraphics::Processor {

std::string StringSplice::GetText() const {
    assert(Source != nullptr);
    assert(Source->IsValid(*this));

    return Source->GetLines().at(LineNumber).substr(Offset, Length);
}

Lexer::Lexer() noexcept {
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

    auto const& line = _lines.at(splice.LineNumber);
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
    _tokenTypes["x"] = EToken::X;
    _tokenTypes["y"] = EToken::Y;
    _tokenTypes["z"] = EToken::Z;
    _tokenTypes["delta"] = EToken::Delta;
    _tokenTypes["red"] = EToken::Red;
    _tokenTypes["green"] = EToken::Green;
    _tokenTypes["blue"] = EToken::Blue;
    _tokenTypes["alpha"] = EToken::Alpha;
    _tokenTypes["rot"] = EToken::Rotation;
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
        _offset = 0;
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
        return AddToken(GatherNumber(), EToken::Number);

    if (std::isspace(current))
        return AddToken(Gather(std::isspace), EToken::WhiteSpace);

    switch (current) {
    case '{': return AddToken(EToken::OpenBrace, 1);
    case '}': return AddToken(EToken::CloseBrace, 1);
    case '(': return AddToken(EToken::OpenParan, 1);
    case ')': return AddToken(EToken::CloseParan, 1);
    case ',': return AddToken(EToken::Comma, 1);
    case '+':
    case '-': {
        if (std::isdigit(Peek())) {
            return AddToken(GatherNumber(), EToken::Number);
        }
        Fail() << "Not Implemented";
        return false;
    }
    default: {}
    }

    // TODO(cjs): error reporting
    if (!_failed) {
        _tokens.emplace_back(Token{ EToken::None });
    }

    return false;
}

char Lexer::Peek() const {
    if (AtEnd()) {
        return 0;
    }

    return GetAt(_offset + 1);
}

bool Lexer::AddToken(EToken type, size_t length) {
    return AddToken(
        StringSplice(*this, _lineNumber, _offset, length), type);
}

bool Lexer::Fail(const char* errorText) const {
    return Fail(errorText);
}

std::ostream& Lexer::Fail() const {
    auto& str = _errorStream;
    str << fileName << ":(" << _lineNumber << "):\n";
    str << "\n" << _lines[_lineNumber] << "\n";
    for (size_t n = 0; n < _offset; ++n) {
        str << ' ';
    }
    str << "^" << std::endl;

    return str;
}

StringSplice Lexer::GatherNumber() const {
    auto hasExponent = false;
    auto hasNumber = false;
    auto hasDot = false;
    auto offset = _offset;
    const auto ch = GetCurrent();
    switch (ch) {
        case '-':
            ++offset;
            break;
        case '+':
            ++offset;
            break;
        default: {}
    }

    while (!AtEndAt(offset)) {
        auto ch = GetAt(offset);
        switch (ch) {
        case '.':
            if (hasDot) {
                Fail() << "Bad number";
                return {};
            }
            hasDot = true;
            break;
        case 'e':
        case 'E':
            if (!hasNumber || hasDot) {
                Fail() << "Bad number";
                return {};
            }
            if (hasExponent) {
                Fail() << "Multiple exponents in Number";
                return {};
            }
            hasExponent = true;
            break;
        default:
            if (!isdigit(ch)) {
                if (!hasNumber) {
                    Fail() << "Bad number";
                    return {};
                }
                return StringSplice(*this, _lineNumber,
                    _offset, offset - _offset);
            }
            hasNumber = true;
            break;
        }

        ++offset;
    }

    return StringSplice(*this, _lineNumber, _offset, offset - _offset);
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
    while (!AtEndAt(end) && predicate(GetAt(end)))
        ++end;

    return { *this, _lineNumber, _offset, end - _offset };
}

bool Lexer::AtEndAt(size_t offset) const noexcept {
    if (_lineNumber >= _lines.size())
        return true;

    return offset >= _lines.at(_lineNumber).size();
}

bool Lexer::AtEnd() const noexcept {
    return AtEndAt(_offset);
}

char Lexer::GetAt(size_t offset) const {
    if (AtEndAt(offset))
        return 0;

    return _lines[_lineNumber][offset];
}

char Lexer::GetCurrent() const noexcept {
    return GetAt(_offset);
}

}  // namespace TurtleGraphics::Processor

