#pragma once
#include <iostream>
#include <sstream>

namespace T1 {
    enum ECommandType {
        None = 0,
        Pen,
        Rotate,
        Move,
        Quit,
    };

    struct Command {
        ECommandType type {};
        bool down {};
        float distance {};
        float rotation {};

        Command() {
            type = ECommandType::None;
        }

        Command(ECommandType _type, float _value) {
            type = _type;
            rotation = distance = _value;
        }

        Command(ECommandType _type, bool _down) {
            type = _type;
            down = _down;
        }

        // TODO move to static StringUtil space
        template <typename Ty>
        static Ty FromString(const std::string &text) {
            Ty value;
            std::istringstream(text) >> value;
            return value;
        }

        static Command Parse(std::string line) {
            if (line.empty())
                return {};

            std::cout << "line: " << line << std::endl;
            const auto cmd = line[0];
            const auto arg = line.substr(1);
            switch (cmd) {
            case 'P':
                //return {Pen, FromString<bool>(arg)};
                return { Pen, true };
            case 'R':
                return {Rotate, FromString<float>(arg)};
            case 'M':
                return {Move, FromString<float>(arg)};
            case 'Q':
            default:
                return {};
            }
        }
    };
}
