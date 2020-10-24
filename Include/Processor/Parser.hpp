// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <string>

#include "Processor/AstNode.hpp"

namespace TurtleGraphics::Processor {

class Parser final : public ProcessBase {
    std::vector<Token> _tokens;
    size_t _currentToken = 0;
    std::vector<AstNodePtr> _context;

public:
    Parser() = default;
    explicit Parser(const Lexer& lexer);

    void SetLexer(const Lexer& lexer);

    bool Run(const Lexer& lexer);
    bool Run() override;

    AstNodePtr GetRoot() const;
    bool AddArguments();

private:
    bool ParseFunction();
    bool ParseColorName();
    bool ParseStatement();
    bool ParseRepeat();
    bool ParseMove();
    bool ParseRotate();
    bool ParseExpression();
    bool ParseStatements();
    bool ParseStatementBlock();

    bool AddStatementBlock();

    std::vector<Token> GetTokens() const { return _tokens; }

    Token CurrentToken() const { return GetTokens().at(_currentToken); }
    EToken CurrentTokenType() const { return CurrentToken().Type; }

    bool CurrentTokenType(EToken type) const {
        return CurrentToken().Type == type;
    }

    std::string CurrentTokenText() const {
        return CurrentToken().Splice.GetText();
    }

    bool AtEnd() const {
        return GetTokens().size() == _currentToken;
    }

    Token NextToken() {
        return GetTokens().at(++_currentToken);
    }

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
