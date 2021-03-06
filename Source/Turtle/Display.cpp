// Copyright � 2020 christian@schladetsch.com

#include "Pch.hpp"
#include "Display.hpp"

#include <utility>

namespace TurtleGraphics {

Display::~Display() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Display::Clear() const noexcept {
    SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(_renderer);
}

bool Display::Bootstrap(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL: %s",
            SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(width, height,
        SDL_WINDOW_RESIZABLE, &_window, &_renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't create window and renderer: %s",
            SDL_GetError());
        return false;
    }

    SDL_SetWindowTitle(_window, "Turtle Graphics++");

    Clear();

    return true;
}

void Display::AddKeyMap(SDL_KeyCode key, KeyResponseFunction function) {
    _keyMappings[key] = std::move(function);
}

bool Display::PreRender() const {
    SDL_Event event;

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        return false;

    if (event.type == SDL_KEYDOWN) {
        const auto code = static_cast<SDL_KeyCode>(event.key.keysym.sym);
        if (_keyMappings.contains(code)) {
            _keyMappings.at(code)();
        }
    }

    return true;
}

void Display::Present() {
    SDL_RenderPresent(_renderer);
}

}  // namespace TurtleGraphics
