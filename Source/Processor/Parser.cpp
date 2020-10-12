// Copyright © 2020 christian@schladetsch.com

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
}

bool Parser::ParseStatements() {
    while (ParseStatement()) {
        continue;
    }

    return HasSucceeded();
}

bool Parser::ParseStatement() {
    switch (CurrentTokenType()) {
    case EToken::PenDown: return AddChild(EToken::PenDown);
    case EToken::PenUp: return AddChild(EToken::PenUp);
    case EToken::Repeat: return ParseRepeat();
    case EToken::Rotate: return ParseRotate();
    case EToken::Move: return ParseMove();
    case EToken::Quit: return AddChild(EToken::Quit);
    case EToken::Function: return ParseFunction();
    case EToken::Number: return AddChild(CurrentToken());
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
        return nullptr;
    }

    return _context.front();
}

bool Parser::ParseFunction() {
    NextToken();

    const auto funName = CurrentToken();

    if (!Expect(EToken::Identifier)) {
        return Fail("Function name expected");
    }

    auto fun = AstNode::New(EToken::Function);
    fun->AddChild(AstNode::New(funName));
    EnterNode(fun);

    if (!AddArguments()) {
        return Fail("Failed to parse arguments");
    }

    if (!AddStatementBlock()) {
        return Fail("Statement block expected");
    }

    LeaveNode();

    return true;
}

bool Parser::AddStatementBlock() {
    EnterNode(AstNode::New(EToken::StatementBlock));
    if (!ParseStatementBlock()) {
        return false;
    }

    LeaveNode();
    return true;
}

bool Parser::AddArguments() {
    if (!Expect(EToken::OpenParan)) {
        return Fail("Open parenthesis expected");
    }

    const auto args = AstNode::New(EToken::ArgList);
    EnterNode(args);

    while (AddChild(EToken::Identifier)) {
        if (!Peek(EToken::Comma)) {
            break;
        }

        NextToken();
    }

    if (!Expect(EToken::CloseParan)) {
        return Fail("Close parenthesis expected");
    }

    LeaveNode();

    return true;
}

void Parser::EnterNode(AstNodePtr const &node) {
    _context.back()->AddChild(node);
    _context.push_back(node);
}

void Parser::LeaveNode() {
    _context.pop_back();
}

bool Parser::ParseStatementBlock() {
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

bool Parser::AddChild(Token const &token) {
    ++_currentToken;
    return AddChild(AstNode::New(token));
}

bool Parser::AddChild(EToken type) {
    return AddChild(Token(type));
}

bool Parser::AddChild(AstNodePtr const &child) {
    _context.back()->AddChild(child);
    return true;
}

}  // namespace TurtleGraphics::Processor 

