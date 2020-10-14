// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <optional>

#include "Command.hpp"
#include "Continuation.hpp"
#include "Continuation.hpp"
#include "Continuation.hpp"
#include "Continuation.hpp"
#include "Turtle.hpp"
#include "Processor/Translator.hpp"

namespace TurtleGraphics { namespace Processor {

class Executor : public ProcessBase {
    vector<CommandSequencePtr> _context;
    vector<Command> _data;
    CommandSequencePtr _commands;
    Turtle* _turtle = nullptr;
    bool _break = false;
    CommandSequencePtr _sequence;

public:
    Executor(Turtle &turtle) noexcept {
        _turtle = &turtle;
    }

    Executor(Turtle& turtle, const CommandSequencePtr sequence) noexcept ;

    bool Run(Turtle& turtle, CommandSequencePtr sequence) noexcept;
    bool Run(CommandSequencePtr sequence) noexcept;
    bool Run() noexcept override;
    std::map<std::string, Command>& GetScope();
    std::optional<Command> PopData() noexcept;

private:
    bool Execute(Continuation& sequence);
    bool Execute(Command const& command);
    bool NextSequence() noexcept;

    template <typename Ty>
    std::optional<Ty> DataPop() noexcept {
        if (_data.empty()) {
            Fail("Data stack empty");
            return std::nullopt;
        }

        try {
            auto top = _data.back();
            _data.pop_back();
            return std::get<Ty>(top.Value);
        } catch (std::exception& e) {
            (void)e;
            Fail("Wrong data type");
        }

        return std::nullopt;
    }

    bool PopFloat(float &num);
    bool DoRepeat();
};
}  // namespace Processor
}  // namespace TurtleGraphics
