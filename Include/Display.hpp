// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <SDL.h>

namespace TurtleGraphics {

class Display {
public:
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

    ~Display();

    [[nodiscard]] bool Bootstrap(int width, int height);
    [[nodiscard]] bool PreRender() const;
    void Present();
};

}  // namespace TurtleGraphics
