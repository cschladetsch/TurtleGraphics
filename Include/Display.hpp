// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <functional>
#include <map>

#include <SDL.h>

namespace TurtleGraphics {

class Display {
public:
    typedef std::function<void()> KeyResponseFunction;

private:
    std::map<SDL_KeyCode, KeyResponseFunction> _keyMappings;
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

public:
    Display() = default;
    ~Display();
    void Clear() const noexcept;

    SDL_Window* GetWindow() const { return _window; }
    SDL_Renderer* GetRenderer() const { return _renderer; }

    void AddKeyMap(SDL_KeyCode key, KeyResponseFunction function);

    [[nodiscard]] bool Bootstrap(int width, int height);
    [[nodiscard]] bool PreRender() const;
    void Present();
};

}  // namespace TurtleGraphics
