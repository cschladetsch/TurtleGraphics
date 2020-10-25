// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <optional>
#include <vector>
#include <map>
#include <string>

#include "Command.hpp"
#include "Continuation.hpp"
#include "Turtle.hpp"
#include "Processor/Translator.hpp"

namespace TurtleGraphics::Processor {

class Executor : public ProcessBase {
    vector<CommandSequencePtr> _context;
    vector<Command> _data;
    CommandSequencePtr _commands;
    Turtle* _turtle = nullptr;
    bool _break = false;
    CommandSequencePtr _sequence;

public:
    explicit Executor(Turtle &turtle) noexcept {
        _turtle = &turtle;
    }

    Executor(Turtle& turtle, CommandSequencePtr const& sequence);

    bool Run(Turtle& turtle, CommandSequencePtr const& sequence);
    bool Run(CommandSequencePtr const& sequence);
    bool Run() override;

    std::map<std::string, Command>& GetScope();
    std::optional<Command> PopData() noexcept;

private:
    bool Execute(Continuation& sequence);
    bool Execute(Command const& command);

    bool NextSequence();

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
        } catch (std::exception const &e) {
            (void)e;
            Fail("Wrong data type");
        }

        return std::nullopt;
    }

    bool PopFloat(float &num);

    bool DoRepeat();
    bool DoDelta();
};

}  // namespace TurtleGraphics::Processor
