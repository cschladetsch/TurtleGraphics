#include "Processor/ProcessorPch.hpp"
#include "Processor/Parser.hpp"

namespace T1 { namespace Processor {

    Parser::Parser(const Lexer& lexer)
    {
        _context.push_back(AstNode::New(Start));
        for (const auto& token : lexer.GetTokens())
        {
            if (token.Type != WhiteSpace)
                _tokens.push_back(token);
        }
    }

    bool Parser::Run()
    {
        return ParseStatements();
    }

    bool Parser::ParseStatements()
    {
        while (ParseStatement())
            ;

        return HasSucceeded();
    }

    bool Parser::ParseStatement()
    {
        switch (CurrentTokenType())
        {
        case PenDown: return AppendChild(PenDown);
        case PenUp: return AppendChild(PenUp);
        case Repeat: return ParseRepeat();
        case Rotate: return ParseRotate();
        case Move: return ParseMove();
        case Quit: return AppendChild(Quit);
        }

        return false;
    }

    bool Parser::ParseRepeat()
    {
        if (!Peek(Number))
            return Fail("Number expected");
        
        EnterNode(AstNode::New(Repeat));
        AddChild(NextToken());

        if (!ParseStatementBlock())
            return false;

        LeaveNode();

        return true;
    }

    AstNodePtr Parser::GetRoot() const 
    {
        if (_context.size() != 1)
        {
            Fail("Unbalanced parse tree");
            return 0;
        }
        
        return _context.front();
    }
    
    void Parser::EnterNode(AstNodePtr node)
    {
        _context.back()->AddChild(node);
        _context.push_back(node);
    }

    void Parser::LeaveNode()
    {
        _context.pop_back();
    }

    bool Parser::ParseStatementBlock()
    {
        NextToken();

        if (!Expect(OpenBrace))
            return false;

        if (!ParseStatements())
            return false;

        if (!Expect(CloseBrace))
            return false;

        return true;
    }

    bool Parser::Expect(EToken type)
    {
        if (!CurrentTokenType(type))
            return Fail("Unexpected different token type");

        ++_currentToken;

        return true;
    }

    bool Parser::ParseRotate()
    {
        return AddParameterisedCommand(Rotate);
    }

    bool Parser::ParseMove()
    {
        return AddParameterisedCommand(Move);
    }

    bool Parser::AddParameterisedCommand(EToken type)
    {
        if (!Peek(Number))
            return Fail("Number expected");

        auto node = AstNode::New(type);
        node->AddChild(AstNode::New(NextToken()));
        ++_currentToken;
        AddChild(node);
        return true;
    }

    bool Parser::ParseExpression()
    {
        return false;
    }

    bool Parser::AppendChild(Token token)
    {
        AddChild(token);
        ++_currentToken;
        return true;
    }

    bool Parser::AddChild(Token token)
    {
        return AddChild(AstNode::New(token));
    }

    bool Parser::AddChild(AstNodePtr node)
    {
        _context.back()->AddChild(node);
        return true;
    }
} }

