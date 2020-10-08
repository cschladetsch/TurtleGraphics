// Copyright 2020 christian@schladetsch.com

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
    bool Translate(AstNodePtr node);
    bool Translate(vector<AstNodePtr> const& children);
    bool TranslateRepeat(AstNodePtr node);

    CommandSequencePtr Enter();
    void Leave();

    CommandSequencePtr Current() const { return _commands.back(); }

    bool Append(Command command) { Current()->Append(command); return true;  }
    bool Append(ECommandType type);

    bool AddUnaryOperation(AstNodePtr node, ECommandType type);

    int MakeValueInt(AstNodePtr node);
    static string MakeValueString(AstNodePtr node);
};
}  // namespace Processor
}  // namespace Turtle1
