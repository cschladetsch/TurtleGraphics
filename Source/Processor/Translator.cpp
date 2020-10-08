// Copyright 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Translator.hpp"

namespace Turtle1 { namespace Processor {
Translator::Translator(AstNodePtr root) {
    _root = root;
}

bool Translator::Run() {
    if (_root == nullptr) {
        return Fail("Empty ast tree");
    }

    if (_root->GetType() != EToken::Start) {
        return Fail("Start expected");
    }

    return Translate(_root);
}

CommandSequencePtr Translator::GetCommands() const {
    return _commands.back();
}

bool Translator::Translate(AstNodePtr node) {
    switch (node->GetType()) {
    case EToken::Start:
        Enter();
        return Translate(node->GetChildren());
    case EToken::Move:
        return AddUnaryOperation(node, ECommandType::Move);
    case EToken::Rotate:
        return AddUnaryOperation(node, ECommandType::Rotate);
    case EToken::Quit:
        return Append(ECommandType::Quit);
    case EToken::PenDown:
        return Append(ECommandType::PenDown);
    case EToken::PenUp:
        return Append(ECommandType::PenUp);
    case EToken::Repeat:
        return TranslateRepeat(node);
    }

    return false;
}

bool Translator::Translate(vector<AstNodePtr> const &children) {
    for (auto const& child : children) {
        if (!Translate(child))
            return false;
    }

    return true;
}

bool Translator::TranslateRepeat(AstNodePtr node) {
    auto const& children = node->GetChildren();
    int numTimes = MakeValueInt(children[0]);

    auto commands = Enter();
    for (size_t n = 1; n < children.size(); ++n) {
        if (!Translate(children[n]))
            return false;
    }
    Leave();
    Append(Command(commands));
    Append(Command(numTimes));
    Append(ECommandType::Repeat);

    return true;
}

CommandSequencePtr Translator::Enter() {
    auto next = std::make_shared<CommandSequence>();
    _commands.push_back(next);
    return next;
}

void Translator::Leave() {
    if (_commands.empty()) {
        Fail("Internal Error: imbalanced translation");
        return;
    }

    _commands.pop_back();
}

bool Translator::Append(ECommandType type) {
    Append(Command(type));
    return true;
}

bool Translator::AddUnaryOperation(AstNodePtr node, ECommandType type) {
    Append(Command(MakeValueInt(node->GetChildren()[0])));
    Append(Command(type));
    return true;
}

int Translator::MakeValueInt(AstNodePtr node) {
    try {
        return std::stoi(node->GetText());
    }
    catch (std::exception& e) {
        (void)e;
        Fail("Couldn't convert to number");
        return 0;
    }
}

string Translator::MakeValueString(AstNodePtr node) {
    return node->GetText();
}

}  // namespace Processor
}  // namespace Turtle1

