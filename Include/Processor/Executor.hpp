// Copyright 2020 christian@schladetsch.com

#pragma once

#include <optional>
#include "Turtle.hpp"
#include "Processor/Translator.hpp"

namespace Turtle1 { namespace Processor {

class Executor : public ProcessBase {
    vector<CommandSequencePtr> _context;
    vector<Command> _data;
    CommandSequencePtr _commands;
    Turtle* _turtle = nullptr;
    bool _break = false;

 public:
    Executor(Turtle &turtle) {
        _turtle = &turtle;
    }

    Executor(Turtle &turtle, CommandSequencePtr sequence)
        : Executor(turtle) {
        _context.push_back(sequence);
    }

    void Run(CommandSequencePtr sequence);
    bool Run();

 private:
     bool Execute(CommandSequence& sequence);
     bool Execute(Command command);
     bool NextSequence();

     template <typename Ty>
     std::optional<Ty> DataPop() {
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
}  // namespace Turtle1
