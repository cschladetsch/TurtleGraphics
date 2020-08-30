#pragma once
#include <SDL_render.h>

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
        void Draw(SDL_Renderer* renderer) const;

    protected:
        Position GetForward() const;
    };
}

