// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/AstNode.hpp"

namespace TurtleGraphics::Processor {

void AstNode::AddChild(const AstNodePtr& node) {
    assert(node);

    _children.emplace_back(node);
}

void AstNode::ForEachChild(const std::function<void(const AstNode&)>& action) {
    assert(action);

    for (auto const& child : _children) {
        action(*child);
    }
}

AstNodePtr AstNode::New(Token token) {
    return std::make_shared<AstNode>(token);
}

}  // namespace TurtleGraphics::Processor

