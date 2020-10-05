#pragma once

#include <list>
#include <string>

#include "Command.hpp"
#include "Position.hpp"

namespace T1
{
    class Turtle
    {
    public:
        Position location {};
        float orientation {};
        bool penDown {};

    private:
        std::list<Command> _commands {};
        std::list<std::pair<Position, bool>> _lineSegments;

    public:
        Turtle() = default;

        void Move(float distance);
        void Rotate(float angle);
        void Draw(SDL_Renderer* renderer) const;
        bool ReadCommands(std::string fileName);

        std::string Trace() const;
        bool ProcessCommands();

    protected:
        Position GetForward() const;
        void DrawTurtle(SDL_Renderer* renderer) const;
        void DrawLineSegments(SDL_Renderer *renderer) const;
    };
}

