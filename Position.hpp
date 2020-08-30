#pragma once

namespace T1
{
    struct Position
    {
        float x, y;

        Position() { }
        Position(float _x, float _y)
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
