// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <functional>
#include <list>
#include <string>
#include <utility>

#include <SDL.h>
#include "Position.hpp"
#include "StdAliases.hpp"

namespace TurtleGraphics {

class Turtle {
public:
    Position Location = { 500, 500 };
    float Orientation = 0;
    bool PenDown = false;

private:
    list<pair<Position, bool>> _lineSegments;

public:
    Turtle() = default;

    void Move(float distance);
    void Rotate(float angle);
    void DrawPath(SDL_Renderer* renderer);
    void DrawTurtle(SDL_Renderer* renderer) const;

    Position Process();
    Position Process(std::function<bool(Turtle&, Position const& next)> const& fun);

    friend std::ostream& operator<<(std::ostream& out, const Turtle &turtle) {
        return out << "Turtle @" << turtle.Location;
    }

protected:
    [[nodiscard]] Position GetForward() const;
    void DrawLineSegments(SDL_Renderer* renderer);
    void ClearHistory();
};

}  // namespace TurtleGraphics
