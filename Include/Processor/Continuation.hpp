// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <optional>
#include <string>
#include <map>
#include <vector>

#include "Config.hpp"
#include "Executor.hpp"
#include "Processor/Command.hpp"
#include "Processor/ProcessBase.hpp"

namespace TurtleGraphics::Processor {

typedef std::string Identifier;
typedef std::map<Identifier, Command> Scope;

class Executor;

class Continuation : public ProcessBase {
    vector<Command> _commands;
    size_t _offset = 0;
    Scope _scope;
    Scope _enteredScope;
    vector<Identifier> _formalArgs;

public:
    Continuation() = default;
    explicit Continuation(vector<Command> commands
        , vector<Identifier> formalArgs = vector<Identifier>());

    bool Run() override;
    void Reset() override;

    bool Enter(Executor& exec);
    Command Next();

    [[nodiscard]] bool HasScoped(Identifier const& identifier) const {
        return _scope.contains(identifier);
    }

    [[nodiscard]] Command GetScoped(Identifier const& identifier) const {
        return _scope.at(identifier);
    }

    [[nodiscard]] std::optional<Command> GetScopedOpt(Identifier const& identifier)
        const {
        return HasScoped(identifier)
            ? std::make_optional(_scope.at(identifier))
            : std::nullopt;
    }

    [[nodiscard]] const Scope& GetScope() const noexcept { return _scope; }
    [[nodiscard]] Scope& GetScope() noexcept { return _scope; }
    [[nodiscard]] bool AtEnd() const noexcept {
        return _offset == _commands.size();
    }

private:
    friend class Translator;

    void Append(const Command& command);
};

}  // namespace TurtleGraphics::Processor

