// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"

#ifndef TURTLE_UNIT_TESTS

#include <iostream>

#include "SDL.h"
#include "Display.hpp"
#include "TurtleGraphics.hpp"

using TurtleGraphics::Display;
using TurtleGraphics::TurtleGraphics;

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    Display display{ };
    if (!display.Bootstrap(1000, 1000)) {
        cerr << "Failed to startup SDL." << endl;
        return -1;
    }

    TurtleGraphics turtle;
    turtle.PenDown = false;
    turtle.Location = { 500, 500 };

    while (display.PreRender()) {
        turtle.Draw(display.Renderer);
        display.Present();
    }

    return 0;
}

#endif  // !TURTLE_UNIT_TESTS
