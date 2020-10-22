// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/Translator.hpp"

namespace TurtleGraphics::Processor {

bool Translator::Run(AstNodePtr root) {
    _root = std::move(root);
    return Run();
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
    if (_commands.size() != 1) {
        Fail("Internal Error: Unbalanced translation");
        return nullptr;
    }

    return _commands.back();
}

bool Translator::TranslateFunction(const AstNodePtr& node) {
    auto const& children = node->GetChildren();
    if (children.size() != 3) {
        return Fail("Internal Error: Functions require 3 AST children.");
    }

    auto const& name = children[0]->GetText();
    auto const& args = children[1]->GetChildren();
    auto const& body = children[2]->GetChildren();

    Append(Command(Translate(body)));
    Append(Command(Translate(args)));
    Append(Command(name));
    Append(ECommandType::Function);

    return true;
}

bool Translator::TranslateArgList(const AstNodePtr& node) const {
    vector<Identifier> idents;
    for (const auto& arg : node->GetChildren()) {
        idents.push_back(arg->GetText());
    }

    return Append(Command(idents));
}

bool Translator::Translate(AstNodePtr const &node) {
    assert(node);
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
    case EToken::ArgList:
        return TranslateArgList(node);
    case EToken::Function:
        return TranslateFunction(node);
    default: ;
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

bool Translator::TranslateRepeat(const AstNodePtr &node) {
    auto const& children = node->GetChildren();
    const auto numTimes = MakeValueInt(children[0]);

    const auto commands = Enter();
    for (size_t n = 1; n < children.size(); ++n) {
        if (!Translate(children[n])) {
            return false;
        }
    }

    Leave();

    Append(Command(commands));
    Append(Command(numTimes));
    Append(ECommandType::Repeat);

    return true;
}

CommandSequencePtr Translator::Enter() {
    auto next = std::make_shared<Continuation>();
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

bool Translator::Append(Command const &command) const {
    Current()->Append(command);
    return true;
}

bool Translator::Append(ECommandType type) const {
    Append(Command(type));
    return true;
}

bool Translator::AddUnaryOperation(AstNodePtr const &node, ECommandType type) const {
    Append(Command(MakeValueInt(node->GetChildren()[0])));
    Append(Command(type));
    return true;
}

int Translator::MakeValueInt(const AstNodePtr &node) const {
    try {
        return std::stoi(node->GetText());
    }
    catch (std::exception& e) {
        (void)e;
        Fail("Couldn't convert to number");
        return 0;
    }
}

string Translator::MakeValueString(const AstNodePtr &node) {
    return node->GetText();
}

}  // namespace TurtleGraphics::Processor

