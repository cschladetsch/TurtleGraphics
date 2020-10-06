// Copyright 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/AstNode.hpp"

namespace Turtle1 { namespace Processor {
    void AstNode::AddChild(AstNodePtr node) {
        assert(node);

        _children.emplace_back(node);
    }

    void AstNode::ForEachChild(std::function<void(const AstNode&)> action) {
        assert(action);

        for (auto const& child : _children) {
            action(*child);
        }
    }

    AstNodePtr AstNode::New(Token token) {
        return std::make_shared<AstNode>(token);
    }
}  // namespace Processor
}  // namespace Turtle1
