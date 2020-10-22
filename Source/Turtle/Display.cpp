// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"
#include "Display.hpp"

namespace TurtleGraphics {

Display::~Display() {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

bool Display::Bootstrap(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL: %s",
            SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(width, height,
        SDL_WINDOW_RESIZABLE, &Window, &Renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't create window and renderer: %s",
            SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(Renderer);

    return true;
}

bool Display::PreRender() const {
    SDL_Event event;

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        return false;

    return true;
}

void Display::Present() {
    SDL_RenderPresent(Renderer);
}
}  // namespace TurtleGraphics
