// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <vector>
#include <string>

#include "Processor/AstNode.hpp"
#include "Processor/CommandSequence.hpp"

namespace Turtle1 { namespace Processor {
class Translator : public ProcessBase {
    vector<CommandSequencePtr> _commands;
    AstNodePtr _root;

public:
    explicit Translator(AstNodePtr root);

    bool Run();

    CommandSequencePtr GetCommands() const;

private:
    bool Translate(AstNodePtr const& node);
    bool Translate(vector<AstNodePtr> const& children);
    bool TranslateRepeat(const AstNodePtr& node);

    CommandSequencePtr Enter();
    void Leave();

    CommandSequencePtr Current() const { return _commands.back(); }

    bool Append(Command command) { Current()->Append(command); return true;  }
    bool Append(ECommandType type);

    bool AddUnaryOperation(AstNodePtr const& node, ECommandType type);

    int MakeValueInt(const AstNodePtr& node) const;
    static string MakeValueString(AstNodePtr node);
};
}  // namespace Processor
}  // namespace Turtle1
