// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <functional>
#include <map>

#include <SDL.h>

namespace TurtleGraphics {

class Display {
    typedef std::function<void()> Function;
    std::map<SDL_KeyCode, Function> _keyMappings;

public:
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

    ~Display();
    void Clear();

    void AddKeyMap(SDL_KeyCode key, Function function);

    [[nodiscard]] bool Bootstrap(int width, int height);
    [[nodiscard]] bool PreRender() const;
    void Present();
};

}  // namespace TurtleGraphics
