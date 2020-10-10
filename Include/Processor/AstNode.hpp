// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "Processor/Token.hpp"

namespace Turtle1::Processor {

class AstNode;

typedef std::shared_ptr<AstNode> AstNodePtr;

class AstNode {
    Token _token;
    vector<AstNodePtr> _children;

 public:
    explicit AstNode(const Token token) : _token(token) { }
    explicit AstNode(const EToken type = EToken::None) : _token(type) { }

    [[nodiscard]] EToken GetType() const { return _token.Type; }
    [[nodiscard]] string GetText() const { return _token.Splice.GetText(); }
    [[nodiscard]] vector<AstNodePtr> const &GetChildren() const { return _children; }

    void AddChild(const AstNodePtr& node);
    void ForEachChild(const std::function<void(const AstNode&)>& action);

    static AstNodePtr New(Token token);
    static AstNodePtr New(EToken token) { return New(Token(token)); }
};
}  // namespace Turtle1::Processor

