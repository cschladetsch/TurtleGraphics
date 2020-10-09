// Copyright 2020 christian@schladetsch.com

#include "Pch.hpp"
#include "Turtle.hpp"

#include <fstream>
#include <iostream>

namespace Turtle1 {

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

    const auto p0 = location + offsets[0];
    const auto p1 = location + offsets[1];
    const auto p2 = location + offsets[2];

    SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
}

void Turtle::DrawLineSegments(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    auto loc = location;
    for (auto ls : _lineSegments) {
        const auto next = loc + ls.first;
        if (true) {
            SDL_RenderDrawLine(renderer
                , loc.x, loc.y, next.x, next.y);
        }

        loc = next;
    }
}

void Turtle::Move(float distance) {
    std::cout << "Move " << distance << std::endl;
    auto end = GetForward()*distance;
    _lineSegments.emplace_back(end, penDown);
}

void Turtle::Rotate(float angle) {
    std::cout << "Rotate " << angle << std::endl;
    orientation += angle;
    while (orientation > 360)
        orientation -= 360;
}

Position Turtle::GetForward() const {
    const float d2f = static_cast<float>(M_PI/180.);
    const float x = cosf(orientation*d2f);
    const float y = sinf(orientation*d2f);
    return { x, y };
}

string Turtle::Trace() const {
    return "Turtle";
}

}  // namespace Turtle1
