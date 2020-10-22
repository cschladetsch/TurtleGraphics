// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"
#include "Turtle.hpp"

#include <iostream>

namespace TurtleGraphics {

int Round(const float x) {
    return x < 0 ? static_cast<int>(x - 0.0f) : static_cast<int>(x + 0.5f);
}

void DrawLine(SDL_Renderer* renderer, const float x, const float y, const float x1, const float y1) {
    SDL_RenderDrawLine(renderer, Round(x), Round(y), Round(x1), Round(y1));
}

void Turtle::DrawPath(SDL_Renderer* renderer) {
    DrawLineSegments(renderer);
    ClearHistory();
}

void Turtle::DrawTurtle(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 20, 155, 80, SDL_ALPHA_OPAQUE);

    auto const len = 20;
    Position offsets[] = {
        { -len, len },
        { 0, -len },
        { len, len },
    };

    const auto p0 = Location + offsets[0];
    const auto p1 = Location + offsets[1];
    const auto p2 = Location + offsets[2];

    DrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
    DrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    DrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
}

void Turtle::DrawLineSegments(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    auto loc = Location;
    for (auto ls : _lineSegments) {
        const auto next = loc + ls.first;
        SDL_RenderDrawLine(renderer
            , loc.x, loc.y, next.x, next.y);

        loc = next;
    }

    Location = loc;
}

void Turtle::Move(float distance) {
    auto end = GetForward()*distance;
    _lineSegments.emplace_back(end, PenDown);
}

void Turtle::Rotate(float angle) {
    Orientation += angle;
    while (Orientation > 360)
        Orientation -= 360;
}

Position Turtle::GetForward() const {
    const auto d2F = static_cast<float>(M_PI/180.);
    const auto x = cosf(Orientation*d2F);
    const auto y = sinf(Orientation*d2F);
    return { x, y };
}

string Turtle::Trace() const {
    return "TurtleGraphics";
}

Position Turtle::Process(std::function<bool (Turtle &, Position const &next)> const& fun) {
    auto loc = Location;
    for (auto ls : _lineSegments) {
        const auto next = loc + ls.first;
        if (!fun(*this, next)) {
            std::cerr << "Failed process predicate\n";
            return loc;
        }

        loc = next;
    }

    return loc;
}

void Turtle::ClearHistory() {
    _lineSegments.clear();
}

Position Turtle::Process() {
    return Process([](auto, auto) { return true; });
}

}  // namespace TurtleGraphics

