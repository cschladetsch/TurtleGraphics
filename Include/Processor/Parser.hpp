#pragma once

#include <stack>
#include "Processor/Lexer.hpp"
#include "Processor/AstNode.hpp"

namespace T1 { namespace Processor {

    class Parser : public ProcessBase
    {
    private:
        const Lexer& _lexer;
        size_t _currentToken = 0;
        std::vector<AstNodePtr> _context;

    public:
        Parser(const Lexer& lexer);

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

        std::vector<Token> GetTokens() const { return _lexer.GetTokens(); }

        Token CurrentToken() const { return GetTokens()[_currentToken]; }
        EToken CurrentTokenType() const { return CurrentToken().Type; }
        std::string CurrentTokenText() const { return CurrentToken().Splice.GetText(); }

        Token NextToken() { return GetTokens()[++_currentToken]; }
        Token Peek() const { return GetTokens()[_currentToken + 1].Type; }
        bool Peek(EToken type) const { return Peek().Type == type; }
        bool Expect(EToken type);

        bool AddChild(Token token);
        bool AppendChild(Token token);
        bool AddChild(AstNodePtr node);
        void EnterNode(AstNodePtr node);
        void LeaveNode();
    };
} }
