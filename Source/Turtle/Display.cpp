// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"
#include "Display.hpp"

namespace Turtle1 {

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
        SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't create window and renderer: %s",
            SDL_GetError());
        return false;
    }

    return true;
}

bool Display::PreRender() const {
    SDL_Event event;

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        return false;

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    return true;
}

void Display::Present() {
    SDL_RenderPresent(renderer);
}
}  // namespace Turtle1
