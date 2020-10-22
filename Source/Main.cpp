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

void ReadAndRunInput(Turtle turtle)
{
    string script;
    cout << "> ";
    cin >> script;
    RunContext runContext(turtle, script.c_str());
    if (!runContext.Run()) {
        cerr << runContext.GetError() << endl;
    }
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
        turtle.Draw(display.Renderer);
        display.Present();

        ReadAndRunInput(turtle);
    }

    return 0;
}

#endif  // !TURTLE_UNIT_TESTS
