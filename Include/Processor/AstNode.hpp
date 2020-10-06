#pragma once

#include <vector>
#include <functional>

#include "Processor/Token.hpp"

namespace T1 { namespace Processor {

    class AstNode;

    typedef std::shared_ptr<AstNode> AstNodePtr;

    class AstNode
    {
        Token _token;
        std::vector<AstNodePtr> _children;

    public:
        AstNode(Token token = EToken::None) : _token(token) { }
        AstNode(EToken type) : _token(type) { }

        EToken GetType() const { return _token.Type; }
        std::string GetText() const { return _token.Splice.GetText(); }
        std::vector<AstNodePtr> const &GetChildren() const { return _children; }

        void AddChild(AstNodePtr node);
        void ForEachChild(std::function<void(const AstNode&)> action);

        static AstNodePtr New(Token token);
    };
} }

