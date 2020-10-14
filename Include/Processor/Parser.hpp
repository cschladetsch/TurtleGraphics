// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <string>

#include "Processor/AstNode.hpp"

namespace TurtleGraphics { namespace Processor {

class Parser final : public ProcessBase {
    std::vector<Token> _tokens;
    size_t _currentToken = 0;
    std::vector<AstNodePtr> _context;

public:
    Parser() = default;
    explicit Parser(const Lexer& lexer);

    void SetLexer(const Lexer& lexer) noexcept;

    bool Run(const Lexer& lexer) noexcept;
    bool Run() noexcept override;

    AstNodePtr GetRoot() const;
    bool ParseArguments();

private:
    bool ParseFunction();
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

    bool AddChild(Token const &token);
    bool AddChild(EToken type);
    bool AddChild(AstNodePtr const &child);

    void EnterNode(AstNodePtr const &node);
    void LeaveNode();

    bool AddParameterisedCommand(EToken type);
};
}  // namespace Processor
}  // namespace TurtleGraphics
