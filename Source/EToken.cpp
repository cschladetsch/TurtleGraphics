// Copyright © 2020 christian@schladetsch.com

#include "Processor/Pch.hpp"
#include "Processor/EToken.hpp"

namespace TurtleGraphics::Processor {

std::string TokenToString(EToken type) {
    switch (type) {
    case EToken::None: return "None";
    case EToken::Start: return "Start";
    case EToken::StatementBlock: return "StatementBlock";
    case EToken::True: return "True";
    case EToken::False: return "False";
    case EToken::Number: return "Number";
    case EToken::Identifier: return "Identifier";
    case EToken::PenDown: return "PenDown";
    case EToken::PenUp: return "PenUp";
    case EToken::Function: return "Function";
    case EToken::OpenParan: return "OpenParan";
    case EToken::CloseParan: return "CloseParan";
    case EToken::ArgList: return "ArgList";
    case EToken::Comma: return "Comma";
    case EToken::OpenBrace: return "OpenBrace";
    case EToken::CloseBrace: return "CloseBrace";
    case EToken::Move: return "Move";
    case EToken::Rotate: return "Rotate";
    case EToken::RotateX: return "RotateX";
    case EToken::RotateY: return "RotateY";
    case EToken::RotateZ: return "RotateZ";
    case EToken::WhiteSpace: return "WhiteSpace";
    case EToken::Quit: return "Quit";
    case EToken::Repeat: return "Repeat";
    case EToken::If: return "If";
    case EToken::Else: return "Else";
    case EToken::While: return "While";
    case EToken::SetPositionComponent: return "SetPositionComponent";
    case EToken::DeltaPositionComponent: return "DeltaPositionComponent";
    case EToken::X: return "X";
    case EToken::Y: return "X";
    case EToken::Z: return "Z,";
    case EToken::SetColorByName: return "SetColorByName";
    case EToken::Delta: return "Delta";
    case EToken::SetColorComponent: return "SetColorComponent";
    case EToken::MulColorComponent: return "MulColorComponent";
    case EToken::Red: return "Red";
    case EToken::Green: return "Green";
    case EToken::Blue: return "Blue";
    case EToken::Alpha: return "Alpha";
    case EToken::Rotation: return "Rotation";
    }

    return "?Token?";
}

std::ostream& operator<<(std::ostream& str, const EToken type) {
    return str << TokenToString(type);
}
    
}

