// Copyright 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Parser.hpp"

namespace Turtle1 { namespace Processor {

    Parser::Parser(const Lexer& lexer) {
        _context.push_back(AstNode::New(EToken::Start));
        auto const& tokens = lexer.GetTokens();

        for (const auto& token : lexer.GetTokens()) {
            if (token.Type != EToken::WhiteSpace)
                _tokens.push_back(token);
        }
    }

    bool Parser::Run() {
        return ParseStatements();
    }

    bool Parser::ParseStatements() {
        while (ParseStatement()) {
        }

        return HasSucceeded();
    }

    bool Parser::ParseStatement() {
        switch (CurrentTokenType()) {
        case EToken::PenDown: return AppendChild(EToken::PenDown);
        case EToken::PenUp: return AppendChild(EToken::PenUp);
        case EToken::Repeat: return ParseRepeat();
        case EToken::Rotate: return ParseRotate();
        case EToken::Move: return ParseMove();
        case EToken::Quit: return AppendChild(EToken::Quit);
        }

        return false;
    }

    bool Parser::ParseRepeat() {
        if (!Peek(EToken::Number))
            return Fail("Number expected");

        EnterNode(AstNode::New(EToken::Repeat));
        AddChild(NextToken());

        if (!ParseStatementBlock())
            return false;

        LeaveNode();

        return true;
    }

    AstNodePtr Parser::GetRoot() const {
        if (_context.size() != 1) {
            Fail("Unbalanced parse tree");
            return 0;
        }

        return _context.front();
    }

    void Parser::EnterNode(AstNodePtr node) {
        _context.back()->AddChild(node);
        _context.push_back(node);
    }

    void Parser::LeaveNode() {
        _context.pop_back();
    }

    bool Parser::ParseStatementBlock() {
        NextToken();

        if (!Expect(EToken::OpenBrace))
            return false;

        if (!ParseStatements())
            return false;

        if (!Expect(EToken::CloseBrace))
            return false;

        return true;
    }

    bool Parser::Expect(EToken type) {
        if (!CurrentTokenType(type))
            return Fail("Unexpected different token type");

        ++_currentToken;

        return true;
    }

    bool Parser::ParseRotate() {
        return AddParameterisedCommand(EToken::Rotate);
    }

    bool Parser::ParseMove() {
        return AddParameterisedCommand(EToken::Move);
    }

    bool Parser::AddParameterisedCommand(EToken type) {
        if (!Peek(EToken::Number))
            return Fail("Number expected");

        auto node = AstNode::New(type);
        node->AddChild(AstNode::New(NextToken()));
        ++_currentToken;
        AddChild(node);
        return true;
    }

    bool Parser::ParseExpression() {
        return false;
    }

    bool Parser::AppendChild(EToken token) {
        return AppendChild(Token{ token });
    }

    bool Parser::AppendChild(Token token) {
        AddChild(token);
        ++_currentToken;
        return true;
    }

    bool Parser::AddChild(Token token) {
        return AddChild(AstNode::New(token));
    }

    bool Parser::AddChild(AstNodePtr node) {
        _context.back()->AddChild(node);
        return true;
    }
}  // namespace Processor
}  // namespace Turtle1

