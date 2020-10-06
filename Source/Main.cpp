// Copyright 2020 christian@schladetsch.com

#include "Pch.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "Display.hpp"
#include "Turtle.hpp"

using Turtle1::Display;
using Turtle1::Turtle;

using std::cout;
using std::cerr;
using std::endl;

int main2(int argc, char *argv[]) {
    Display display{ };
    if (!display.Bootstrap(1000, 1000)) {
        cerr << "Failed to startup SDL.\n";
        return -1;
    }

    Turtle turtle;
    turtle.penDown = false;
    turtle.location = { 500, 500 };

    cout << turtle.Trace() << endl;

    while (display.PreRender()) {
        turtle.Draw(display.renderer);
        display.Present();
    }

    return 0;
}
