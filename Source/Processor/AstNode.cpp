#include "Processor/ProcessorPch.hpp"
#include "Processor/AstNode.hpp"

namespace T1 { namespace Processor {
    void AstNode::AddChild(AstNodePtr node)
    {
        assert(node);

        _children.emplace_back(node);
    }

    void AstNode::ForEachChild(std::function<void(const AstNode&)> action)
    {
        assert(action);

        for (auto const& child : _children)
        {
            action(*child);
        }
    }

    AstNodePtr AstNode::New(Token token)
    {
        return std::make_shared<AstNode>(token);
    }
} }
