// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <optional>

#include "Config.hpp"
#include "Executor.hpp"
#include "Processor/Command.hpp"

namespace Turtle1::Processor {

typedef std::string Identifier;
typedef std::map<Identifier, Command> Scope;

class Continuation : public ProcessBase {
    vector<Command> _commands;
    size_t _offset = 0;
    Scope _scope;
    Scope _scopeEntered;
    vector<Identifier> _formalArgs;

public:
    Continuation() = default;
    explicit Continuation(vector<Command> commands);

    bool Run() noexcept override;
    void Reset() noexcept override;
    bool Enter(Executor& exec);
    Command Next();
    void Leave(Executor& exec);

    bool HasScoped(Identifier const& identifier) const noexcept {
        return _scope.contains(identifier);
    }

    Command GetScoped(Identifier const& identifier) const {
        return _scope.at(identifier);
    }

    std::optional<Command> GetScopedOpt(Identifier const& identifier) const noexcept {
        return HasScoped(identifier)
            ? std::make_optional(_scope.at(identifier))
            : std::nullopt;
    }

    const Scope& GetScope() const noexcept{ return _scope; }
    Scope& GetScope() noexcept { return _scope; }

    bool AtEnd() const noexcept { return _offset == _commands.size(); }

private:
    friend class Translator;

    void Append(const Command& command);
};

}  // namespace Turtle1::Processor

