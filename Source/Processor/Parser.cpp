// Copyright � 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Parser.hpp"

namespace TurtleGraphics::Processor {

Parser::Parser(const Lexer& lexer) {
    SetLexer(lexer);
}

void Parser::SetLexer(const Lexer& lexer) noexcept {
    _context.push_back(AstNode::New(EToken::Start));
    auto const& tokens = lexer.GetTokens();

    for (const auto& token : lexer.GetTokens()) {
        if (token.Type != EToken::WhiteSpace)
            _tokens.push_back(token);
    }
}

bool Parser::Run(const Lexer& lexer) noexcept {
    SetLexer(lexer);
    return Run();
}

bool Parser::Run() noexcept {
    try {
        return ParseStatements();
    } catch (std::exception &e) {
        Fail() << e.what();
        return false;
    }

    return true;
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
    case EToken::Function: return ParseFunction();
    default: ;
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

bool Parser::ParseArguments(AstNodePtr const &fun) {
    const auto args = AstNode::New(EToken::ArgList);
    EnterNode(args);

    while (Peek(EToken::Identifier)) {
        if (!Peek(EToken::Comma)) {
            break;
        }

        NextToken();
    }

    if (!Expect(EToken::CloseParan)) {
        return Fail("Close parenthesis expected");
    }

    LeaveNode();
    fun->AddChild(args);

    return false;
}

bool Parser::ParseFunction() {
    if (!Expect(EToken::Identifier)) {
        return Fail("Function identifier expected");
    }

    const auto funName = CurrentToken();

    if (!Expect(EToken::OpenParan)) {
        return Fail("Open parenthesis expected");
    }

    auto fun = AstNode::New(EToken::Function);
    fun->AddChild(AstNode::New(funName));

    if (!ParseArguments(fun)) {
        return false;;
    }

    if (!ParseStatementBlock()) {
        return Fail("Statement block expected");
    }

    LeaveNode();
    AddChild(fun);

    return true;
}

void Parser::EnterNode(const AstNodePtr node) {
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

bool Parser::AddChild(const AstNodePtr node) {
    _context.back()->AddChild(node);
    return true;
}

}  // namespace TurtleGraphics::Processor 

