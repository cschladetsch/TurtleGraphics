// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <list>
#include <string>
#include <utility>

#include <SDL.h>
#include "Position.hpp"
#include "StdAliases.hpp"

namespace Turtle1 {

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
    void Draw(SDL_Renderer* renderer) const;

    string Trace() const;

protected:
    [[nodiscard]] Position GetForward() const;
    void DrawTurtle(SDL_Renderer* renderer) const;
    void DrawLineSegments(SDL_Renderer *renderer) const;
};

}  // namespace Turtle1

