#define SDL_MAIN_HANDLED

#include <iostream>
#include "SDL.h"
#include "Display.hpp"
#include "Turtle.hpp"

using namespace T1;

int main(int argc, char *argv[])
{
    Display display{ };
    if (!display.Bootstrap(1000, 1000))
    {
        std::cerr << "Failed to startup SDL.\n";
        return -1;
    }

    Turtle turtle;
    turtle.PenDown = false;
    turtle.Location = { 500,500 };

    while (display.PreRender())
    {
        // TODO: handle input from file
        // TODO: handle input from app
        turtle.Draw(display.renderer);
        display.Present();
    }

    return 0;
}
