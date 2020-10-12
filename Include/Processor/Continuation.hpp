// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <optional>

#include "Config.hpp"
#include "Executor.hpp"
#include "Processor/Command.hpp"

namespace TurtleGraphics::Processor {

typedef std::string Identifier;
typedef std::map<Identifier, Command> Scope;

class Continuation final : public ProcessBase {
    vector<Command> _commands;
    size_t _offset = 0;
    Scope _scope;
    Scope _enteredScope;
    vector<Identifier> _formalArgs;
    // TODO(cjs) Logger<Continuation> _log;

public:
    Continuation() = default;
    explicit Continuation(vector<Command>&& commands, vector<Identifier>&& formalArgs = vector<Identifier>());

    bool Run() noexcept override;
    void Reset() noexcept override;

    bool Enter(Executor& exec);
    Command Next();

    [[nodiscard]] bool HasScoped(Identifier const& identifier) const noexcept {
        return _scope.contains(identifier);
    }

    [[nodiscard]] Command GetScoped(Identifier const& identifier) const {
        return _scope.at(identifier);
    }

    [[nodiscard]] std::optional<Command> GetScopedOpt(Identifier const& identifier) const noexcept {
        return HasScoped(identifier)
            ? std::make_optional(_scope.at(identifier))
            : std::nullopt;
    }

    [[nodiscard]] const Scope& GetScope() const noexcept{ return _scope; }
    [[nodiscard]] Scope& GetScope() noexcept { return _scope; }

    [[nodiscard]] bool AtEnd() const noexcept { return _offset == _commands.size(); }

private:
    friend class Translator;

    void Append(const Command& command);
};

}  // namespace TurtleGraphics::Processor

