#include "Turtle.hpp"

namespace T1
{
    // draw a triangle to represent the turtle
        /*
         *      2
         *      P
         *    1   3
         */
    void Turtle::Draw(SDL_Renderer* renderer) const
    {
        SDL_SetRenderDrawColor(renderer, 20, 255, 80, SDL_ALPHA_OPAQUE);
        Position offsets[] = 
        {
            {-100,100},
            {0,-100},
            {100,100},
        };

        const auto p0 = Location + offsets[0];
        const auto p1 = Location + offsets[1];
        const auto p2 = Location + offsets[2];

        SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
    }

    void Turtle::Move(float distance)
    {
    }

    void Turtle::Rotate(float angle)
    {
    }
    
    Position Turtle::GetForward() const
    {
        return Position();
    }
}
