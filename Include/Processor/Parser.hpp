// Copyright 2020 christian@schladetsch.com

#pragma once

#include <stack>
#include <vector>
#include <string>

#include "Processor/Lexer.hpp"
#include "Processor/AstNode.hpp"

namespace Turtle1 { namespace Processor {
class Parser : public ProcessBase {
 private:
    std::vector<Token> _tokens;
    size_t _currentToken = 0;
    std::vector<AstNodePtr> _context;

 public:
    explicit Parser(const Lexer& lexer);
    bool Run() override;
    AstNodePtr GetRoot() const;

 private:
    bool ParseStatement();
    bool ParseRepeat();
    bool ParseMove();
    bool ParseRotate();
    bool ParseExpression();
    bool ParseStatements();
    bool ParseStatementBlock();

    std::vector<Token> GetTokens() const { return _tokens; }

    Token CurrentToken() const { return GetTokens()[_currentToken]; }
    EToken CurrentTokenType() const { return CurrentToken().Type; }
    bool CurrentTokenType(EToken type) const {
        return CurrentToken().Type == type;
    }
    std::string CurrentTokenText() const {
        return CurrentToken().Splice.GetText();
    }

    Token NextToken() { return GetTokens()[++_currentToken]; }
    Token Peek() const { return Token{ GetTokens()[_currentToken + 1].Type }; }
    bool Peek(EToken type) const { return Peek().Type == type; }
    bool Expect(EToken type);

    bool AddChild(Token token);
    bool AppendChild(EToken token);
    bool AppendChild(Token token);
    bool AddChild(AstNodePtr node);
    void EnterNode(AstNodePtr node);
    void LeaveNode();

    bool AddParameterisedCommand(EToken type);
};
}  // namespace Processor
}  // namespace Turtle1
