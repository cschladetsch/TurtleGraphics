#include <assert.h>
#include "Processor/Lexer.hpp"

namespace T1 { namespace Processor {

    std::string StringSplice::GetText() const
    {
        assert(Source != nullptr);
        assert(Source->IsValid(*this));

        return Source->GetLines()[LineNumber].substr(Offset, Length);
    }

    Lexer::Lexer(const char* text)
    {
        AddText(text);
        AddTokenNames();
    }

    bool Lexer::IsValid(StringSplice splice) const
    {
        if (splice.LineNumber >= _lines.size())
            return false;

        auto const& line = _lines[splice.LineNumber];
        return splice.Offset < line.size() 
            && splice.Offset + splice.Length < line.size();
    }

    void Lexer::AddTokenNames()
    {
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
    }

    void Lexer::AddText(const char *text)
    {
        const char* start = text;
        while (text && *text)
        {
            auto ch = *text;
            if (ch == '\n')
            {
                _lines.push_back(std::string(start, text + 1));
                start = text + 1;
            }

            ++text;
        }

        _lines.push_back(std::string(start, text + 1));
    }

    bool Lexer::Run()
    {
        _failed = false;
        while (GetNext())
            ;

        return !_failed;
    }

    bool Lexer::GetNext()
    {
        if (AtEnd())
            return false;

        if (std::isalpha(GetCurrent()))
        {
            auto splice = Gather(std::isalpha);
            auto text = splice.GetText();
            auto tokenType = _tokenTypes.find(text);
            if (tokenType != _tokenTypes.end())
                return AddToken(splice, tokenType->second);

            return AddToken(splice, EToken::Identifier);
        }

        if (std::isdigit(GetCurrent()))
            return AddToken(Gather(std::isdigit), EToken::Number);
        
        if (std::isspace(GetCurrent()))
            return AddToken(Gather(std::isspace), EToken::WhiteSpace);

        // TODO: error reporting
        _failed = GetCurrent() != 0;
        if (!_failed)
            _tokens.emplace_back(Token{ None });

        return false;
    }

    bool Lexer::AddToken(StringSplice splice, EToken type)
    {
        _tokens.emplace_back(Token{ type, splice });
        _offset += splice.Length;
        return true;
    }

    StringSplice Lexer::Gather(std::function<bool (char)> predicate)
    {
        std::size_t end = _offset;
        while (!AtEnd(end) && predicate(GetCurrent(end)))
            ++end;

        return { *this, _lineNumber, _offset, end - _offset };
    }

    bool Lexer::AtEnd(size_t offset) const
    {
        if (_lineNumber == _lines.size())
            return false;

        return offset >= _lines[_lineNumber].size();
    }

    bool Lexer::AtEnd() const
    {
        return AtEnd(_offset);
    }

    char Lexer::GetCurrent(size_t offset) const
    {
        if (AtEnd(offset))
            return 0;

        return _lines[_lineNumber][offset];
    }

    char Lexer::GetCurrent() const
    {
        return GetCurrent(_offset);
    }
} }

