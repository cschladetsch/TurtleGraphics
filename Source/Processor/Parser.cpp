#include "Processor/ProcessorPch.hpp"
#include "Processor/Parser.hpp"

namespace T1 { namespace Processor {
    Parser::Parser(const Lexer& lexer)
        : _lexer(lexer)
    {
        _context.push_back(AstNode::New(Start));
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
        case WhiteSpace: 
        {
            ++_currentToken;
            return true;
        }
        case PenDown: return AppendChild(PenDown);
        case PenUp: return AppendChild(PenUp);
        case Repeat: return ParseRepeat();
        case Rotate: return ParseRotate();
        case Move: return ParseMove();
        case Quit: return false;
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

        return false;
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
        if (!Peek(type))
            return Fail("Unexpected token type");

        ++_currentToken;

        return true;
    }

    bool Parser::ParseRotate()
    {
        if (!Peek(Number))
            return Fail("Angle expected");

        auto rotate = AstNode::New(Rotate);
        rotate->AddChild(AstNode::New(NextToken()));
        AddChild(rotate);
        return true;
    }

    bool Parser::ParseMove()
    {
        if (!Peek(Number))
            return Fail("Distance expected");

        auto move = AstNode::New(Move);
        move->AddChild(AstNode::New(NextToken()));
        AddChild(move);
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
