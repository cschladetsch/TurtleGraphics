// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <string>

#include "Processor/AstNode.hpp"
#include "Processor/Continuation.hpp"

namespace Turtle1::Processor {

class Translator final : public ProcessBase {
    vector<CommandSequencePtr> _commands;
    AstNodePtr _root;

public:
    explicit Translator(AstNodePtr root);

    bool Run() noexcept override;

    CommandSequencePtr GetCommands() const;

private:
    bool Translate(AstNodePtr const& node);
    bool Translate(vector<AstNodePtr> const& children);
    bool TranslateRepeat(const AstNodePtr& node);

    CommandSequencePtr Enter();
    void Leave();

    CommandSequencePtr Current() const { return _commands.back(); }

    bool Append(Command command) const;
    bool Append(ECommandType type) const;

    bool AddUnaryOperation(AstNodePtr const& node, ECommandType type) const;

    int MakeValueInt(const AstNodePtr& node) const;
    static string MakeValueString(const AstNodePtr& node);
};

}  // namespace Turtle1::Processor
