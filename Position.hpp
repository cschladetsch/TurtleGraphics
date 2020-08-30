#pragma once

namespace T1
{
    struct Position
    {
        int x, y;

        Position() { }
        Position(int _x, int _y)
        {
            x = _x;
            y = _y;
        }

        friend Position operator+(const Position& A, const Position& B)
        {
            return {A.x + B.x, A.y + B.y};
        }
    };

    
}
