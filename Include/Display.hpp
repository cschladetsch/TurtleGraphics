// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <SDL.h>

namespace Turtle1 {

class Display {
public:
    SDL_Window* window = 0;
    SDL_Renderer* renderer = 0;

    ~Display();

    bool Bootstrap(int width, int height);
    bool PreRender() const;
    void Present();
};

}  // namespace Turtle1
