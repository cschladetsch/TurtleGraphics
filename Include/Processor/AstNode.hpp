// Copyright 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "Processor/Token.hpp"

namespace Turtle1 { namespace Processor {

class AstNode;

typedef std::shared_ptr<AstNode> AstNodePtr;

class AstNode {
    Token _token;
    std::vector<AstNodePtr> _children;

 public:
    explicit AstNode(Token token) : _token(token) { }
    explicit AstNode(EToken type = EToken::None) : _token(type) { }

    EToken GetType() const { return _token.Type; }
    std::string GetText() const { return _token.Splice.GetText(); }
    std::vector<AstNodePtr> const &GetChildren() const { return _children; }

    void AddChild(AstNodePtr node);
    void ForEachChild(std::function<void(const AstNode&)> action);

    static AstNodePtr New(Token token);
    static AstNodePtr New(EToken token) { return New(Token(token)); }
};
}  // namespace Processor
}  // namespace Turtle1

