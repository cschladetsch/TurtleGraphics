// Copyright © 2020 christian@schladetsch.com

#include "Pch.hpp"

#ifndef TURTLE_UNIT_TESTS

#include <iostream>
#include <fstream>

#include "Display.hpp"
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
    cout << "turtle> ";
    char buffer[9546];
    if (!cin.getline(buffer, 9546)) {
        return false;
    }

    RunContext runContext(turtle, buffer);
    if (!runContext.Run()) {
        cout << runContext.GetError() << endl;
    }

    return true;
}

std::string ReadAllText(const char* fileName) {
    return (std::stringstream() << std::ifstream(fileName).rdbuf()).str();
}

void RunCommands(Turtle& turtle, const char* fileName) {
    const auto commands = ReadAllText(fileName);
    RunContext context(turtle, commands.c_str());
    if (!context.Run()) {
        cout << context.GetError() << endl;
    }
}

void AddKeyMappings(Display &display, Turtle &turtle) {
    display.AddKeyMap(SDLK_ESCAPE, []() noexcept {
        exit(0);
    });

    display.AddKeyMap(SDLK_l, [&turtle]() {
        RunCommands(turtle, "commands.turtle");
    });
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

    AddKeyMappings(display, turtle);

    while (display.PreRender()) {
        turtle.DrawPath(display.GetRenderer());
        display.Present();

         if (!ReadAndRunInput(turtle)) {
            cout << "Error\n";
         }
    }

    return 0;
}

#endif  // !TURTLE_UNIT_TESTS
