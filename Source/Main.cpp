#include "Pch.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "Display.hpp"
#include "Turtle.hpp"

using T1::Display;
using T1::Turtle;

int main2(int argc, char *argv[]) {
    Display display{ };
    if (!display.Bootstrap(1000, 1000)) {
        std::cerr << "Failed to startup SDL.\n";
        return -1;
    }

    Turtle turtle;
    turtle.penDown = false;
    turtle.location = { 500, 500 };

    if (!turtle.ReadCommands("Commands.txt")) {
        std::cerr << "Failed to read commands\n";
        return - 1;
    }

    // if (!turtle.ProcessCommands())
    // {
    //    std::cerr << "Failed to execute commands\n";
    //    return - 1;
    // }

    std::cout << turtle.Trace() << std::endl;

    while (display.PreRender()) {
        // TODO(cjs): handle input from app
        turtle.Draw(display.renderer);
        display.Present();
    }

    return 0;
}
