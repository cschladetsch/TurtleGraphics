// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <string>
#include <utility>

#include "Processor/AstNode.hpp"
#include "Processor/Continuation.hpp"

namespace TurtleGraphics::Processor {

class Translator : public ProcessBase {
    vector<CommandSequencePtr> _commands;
    AstNodePtr _root;

public:
    Translator() = default;
    explicit Translator(AstNodePtr root) : _root(move(root)) { }

    bool Run() override;
    bool Run(AstNodePtr root);

    CommandSequencePtr GetCommands() const;

private:
    bool Translate(AstNodePtr const& node);
    bool Translate(vector<AstNodePtr> const& children);
    bool TranslateRepeat(const AstNodePtr& node);
    bool TranslateArgList(const AstNodePtr& node) const;
    bool TranslateFunction(const AstNodePtr& node);
    bool TranslateDelta(const AstNodePtr& node);

    CommandSequencePtr Enter();
    void Leave();

    CommandSequencePtr Current() const noexcept { return _commands.back(); }

    bool Append(Command const& command) const;
    bool Append(ECommandType type) const;
    bool AddUnaryOperation(AstNodePtr const& node, ECommandType type) const;

    int MakeValueInt(const AstNodePtr& node) const;
    static string MakeValueString(const AstNodePtr& node);
};

}  // namespace TurtleGraphics::Processor
