// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/RunContext.hpp"

namespace Turtle1::Processor {

//bool RunContext::Run(const char* text) {
//    Reset();
//
//    _lexer = Lexer(text);
//    if (!_lexer.Run())
//        return false;
//
//    _parser = Parser(_lexer);
//    if (!_parser.Run())
//        return false;
//
//    _translator = Translator(_parser.GetRoot());
//    if (!_translator.Run())
//        return false;
//
//    return _executor.Run(_translator.GetCommands());
//}
//
bool RunContext::Run() {
    return HasSucceeded();
}

}
