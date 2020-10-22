// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"
#include "Turtle.hpp"

#include <iostream>

namespace TurtleGraphics {

void Turtle::Draw(SDL_Renderer* renderer) const {
    DrawTurtle(renderer);
    DrawLineSegments(renderer);
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

    SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
}

void Turtle::DrawLineSegments(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    auto loc = Location;
    for (auto ls : _lineSegments) {
        const auto next = loc + ls.first;
        SDL_RenderDrawLine(renderer
            , loc.x, loc.y, next.x, next.y);

        loc = next;
    }
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

bool Turtle::Process(std::function<bool (Turtle const &)> const &fun) {
    auto loc = Location;
    for (auto ls : _lineSegments) {
        const auto next = loc + ls.first;
        if (!fun(*this)) {
            return false;
        }

        loc = next;
    }

    Location = loc;

    return true;
}

bool Turtle::Process() {
    return Process([](auto) { return true; });
}

}  // namespace TurtleGraphics

