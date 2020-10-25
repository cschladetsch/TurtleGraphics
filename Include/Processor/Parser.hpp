// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <string>

#include "Processor/AstNode.hpp"

namespace TurtleGraphics::Processor {

class Parser final : public ProcessBase {
    Lexer const* _lexer = 0;
    size_t _currentToken = 0;
    vector<Token> _tokens;
    vector<AstNodePtr> _context;

public:
    Parser() = default;
    explicit Parser(const Lexer& lexer);

    void SetLexer(const Lexer& lexer);

    bool Run() override;
    bool Run(const Lexer& lexer);

    AstNodePtr GetRoot() const;

protected:
    bool Fail(const char* text) const override {
        Fail() << "Parser : " << text;
        return false;
    }

    std::ostream& Fail() const override {
        return ErrorStream() << "Parser: ";
    }

private:
    bool ParseStatement();
    bool ParseStatements();
    bool ParseExpression();
    bool ParseStatementBlock();
    bool ParseRepeat();
    bool ParseMove();
    bool ParseRotate();
    bool ParseFunction();
    bool ParseColorName();
    bool ParseDelta();

    bool AddStatementBlock();
    bool AddDelta(EToken type);
    bool AddArguments();

    vector<Token> GetTokens() const { return _tokens; }

    Token CurrentToken() const { return GetTokens().at(_currentToken); }
    EToken CurrentTokenType() const { return CurrentToken().Type; }

    bool CurrentTokenType(EToken type) const {
        return CurrentToken().Type == type;
    }

    string CurrentTokenText() const {
        return CurrentToken().Splice.GetText();
    }

    bool AtEnd() const {
        return GetTokens().size() == _currentToken;
    }

    Token NextToken();

    Token Peek() const { return Token{ GetTokens().at(_currentToken + 1).Type }; }
    bool Peek(EToken type) const { return Peek().Type == type; }
    bool Expect(EToken type);

    bool AddChild(Token const &token);
    bool AddChild(EToken type);
    bool AddChild(AstNodePtr const &child);

    void EnterNode(AstNodePtr const &node);
    void LeaveNode();

    bool AddParameterisedCommand(EToken type);
};

}  // namespace TurtleGraphics::Processor

