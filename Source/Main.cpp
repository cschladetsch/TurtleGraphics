// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"

#ifndef TURTLE_UNIT_TESTS

#include <iostream>

#include "SDL.h"
#include "Display.hpp"
#include "Processor/Executor.hpp"
#include "Processor/RunContext.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;

using TurtleGraphics::Display;
using TurtleGraphics::Turtle;
using TurtleGraphics::Processor::RunContext;

bool ReadAndRunInput(Turtle &turtle) {
    cout << "> ";
    char buffer[9546];
    if (!cin.getline(buffer, 9546)) {
        return false;
    }

    RunContext runContext(turtle, buffer);
    if (!runContext.Run()) {
        cout << runContext.GetError() << endl;
    }

    // TODO(cjs)
    //turtle.Draw();

    return true;
}

int main(int argc, char *argv[]) {
    Display display{ };
    if (!display.Bootstrap(1000, 1000)) {
        cerr << "Failed to startup SDL." << endl;
        return -1;
    }

    Turtle turtle;
    turtle.PenDown = false;
    turtle.Location = { 500, 500 };

    while (display.PreRender()) {
        turtle.DrawPath(display.Renderer);
        display.Present();

        if (!ReadAndRunInput(turtle)) {
            cout << "Error\n";
        }
    }

    return 0;
}

#endif  // !TURTLE_UNIT_TESTS
