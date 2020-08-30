#pragma once
#include "Position.hpp"

namespace T1
{
    class Turtle
    {
    public:
        Position Location;
        float Orientation;
        bool PenDown;

    public:
        void Move(float distance);
        void Rotate(float angle);

    protected:
        Position GetForward() const;
    };
}

