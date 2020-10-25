// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <variant>
#include <memory>
#include <string>
#include <vector>

#include "Processor/ECommandType.hpp"

namespace TurtleGraphics::Processor {

class Continuation;
typedef std::shared_ptr<Continuation> CommandSequencePtr;

struct Command {
    ECommandType Type;
    std::variant<int, float, string, CommandSequencePtr, vector<string>> Value;

    Command() noexcept : Command(ECommandType::None) {
    }

    explicit Command(const ECommandType type) noexcept {
        Type = type;
    }

    explicit Command(const string& text) : Value(text) {
        Type = ECommandType::Value;
    }

    explicit Command(int num) : Command(ECommandType::Value) {
        Value = num;
    }

    explicit Command(float num) : Command(ECommandType::Value) {
        Value = num;
    }

    explicit Command(const CommandSequencePtr& commands) noexcept
        : Value(commands) {
        Type = ECommandType::Value;
    }

    explicit Command(vector<string> const& idents)
        : Type(ECommandType::Value), Value(idents) { }
};

}  // namespace TurtleGraphics::Processor
