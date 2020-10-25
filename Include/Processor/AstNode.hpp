// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <functional>


#include "Command.hpp"
#include "Processor/Token.hpp"

namespace TurtleGraphics::Processor {

class AstNode;

typedef std::shared_ptr<AstNode> AstNodePtr;

class AstNode {
    Token _token;
    vector<AstNodePtr> _children;

 public:
    explicit AstNode(const Token token) noexcept : _token(token) { }
    explicit AstNode(const EToken type = EToken::None) noexcept
        : _token(type) { }

    EToken GetType() const noexcept { return _token.Type; }
    string GetText() const { return _token.Splice.GetText(); }
    vector<AstNodePtr> const &GetChildren() const noexcept { return _children; }
    void ForEachChild(const std::function<void(const AstNode&)>& action);

    void AddChild(const AstNodePtr& node);
    void AddChild(EToken type);
    void AddChild(Token token);
    float GetFloat() const;

    static AstNodePtr New(Token token);
    static AstNodePtr New(EToken token) { return New(Token(token)); }
};

}  // namespace TurtleGraphics::Processor

