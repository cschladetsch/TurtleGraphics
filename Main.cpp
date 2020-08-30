#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "Turtle.hpp"

class Display
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    ~Display()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool Bootstrap(int width, int height)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
            return false;
        }

        if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    bool Step() const
    {
        SDL_Event event;

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            return false;

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        return true;
    }
};

int main(int argc, char *argv[])
{
    Display display{ };
    display.Bootstrap(1000, 1000);

    while (display.Step())
    {
        /* do nothing */;
    }

    return 0;
}
