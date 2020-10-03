#define SDL_MAIN_HANDLED

#include <iostream>
#include "SDL.h"
#include "Display.hpp"
#include "Turtle.hpp"

using namespace T1;

int main2(int argc, char *argv[])
{
    Display display{ };
    if (!display.Bootstrap(1000, 1000))
    {
        std::cerr << "Failed to startup SDL.\n";
        return -1;
    }

    Turtle turtle;
    turtle.penDown = false;
    turtle.location = { 500,500 };

    if (!turtle.ReadCommands("Commands.txt"))
    {
        std::cerr << "Failed to read commands\n";
        return - 1;
    }

    //if (!turtle.ProcessCommands())
    //{
    //    std::cerr << "Failed to execute commands\n";
    //    return - 1;
    //}

    std::cout << turtle.Trace() << std::endl;

    while (display.PreRender())
    {
        // TODO: handle input from app
        turtle.Draw(display.renderer);
        display.Present();
    }

    return 0;
}
