// Copyright 2020 christian@schladetsch.com
#ifndef TURTLE_UNIT_TESTS

#include "Pch.hpp"
#include <iostream>

#include "SDL.h"
#include "Display.hpp"
#include "Turtle.hpp"

using Turtle1::Display;
using Turtle1::Turtle;

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    Display display{ };
    if (!display.Bootstrap(1000, 1000)) {
        cerr << "Failed to startup SDL." << endl;
        return -1;
    }

    Turtle turtle;
    turtle.penDown = false;
    turtle.location = { 500, 500 };

    while (display.PreRender()) {
        turtle.Draw(display.renderer);
        display.Present();
    }

    return 0;
}

#endif // !TURTLE_UNIT_TESTS
