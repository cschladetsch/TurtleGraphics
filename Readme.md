# Turtle Graphics
[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/TurtleGraphics/badge)](https://www.codefactor.io/repository/github/cschladetsch/TurtleGraphics)
[![License](https://img.shields.io/github/license/cschladetsch/TurtleGraphics.svg?label=License&maxAge=86400)](./LICENSE)
![Release](https://img.shields.io/github/release/cschladetsch/TurtleGraphics.svg?label=Release&maxAge=60)

A cross-platform [Turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics) system written using modern C++ and SDL, and best practices.

Has both native Visual Studio project for ease of use and access, and fast build speeds. Also has a CMake-based system for cross-platform support (Linux, macOS, etc).

Features:
* [Modern C++](https://github.com/cschladetsch/TurtleGraphics/wiki/ModernCpp), and [SDL](http://www.libsdl.org)
* Implementation of [turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics), with an [interpreter](https://github.com/cschladetsch/TurtleGraphics/wiki/Interperter)
* Trying to show [best practices](https://github.com/cschladetsch/TurtleGraphics/wiki/CppBestPractises)
* Passes [Google C++ lint](https://en.wikipedia.org/wiki/Cpplint) with some [filters](#google-lint-filters)

See [YouTube Playlist](https://youtube.com/sp4m) for real-time video commentary on development.

## Building

You will need to install *SDL* into the `External` folder from the root folder of the project. Up to you how you do this.

Either use the *Visual Studio solution* directly, or CMake otherwise.

### Using CMake

The usual:
```bash
$ mkdir -p build && cd build && cmake .. && make
```

## Development Videos

* [Setup](https://www.youtube.com/watch?v=YXAmNWvC77M) and quick short [follow up](https://www.youtube.com/watch?v=tlwz-TaYKTk).
  * Setup Solution, tools and libs for Visual Studio 2019
  * Get an SDL window up, after building SDL from source
  * Draw a turtle
* [Add Interpreter Structure](https://www.youtube.com/watch?v=rBfrGET-t-4)
* [Add Lexer](https://www.youtube.com/watch?v=eeoNcG8TW8s)
* [Add Parser](https://www.youtube.com/watch?v=DpMwADQnzb0)
* [Add Executor](https://www.youtube.com/watch?v=ywQ5dmP9Gy4)
* [Add Translator](https://www.youtube.com/watch?v=g0glGzOOaWo)

#### Google Lint Filters

These are the filters I use for Google's `cpplint` to suite my tastes more. The `bash` function I use is:

```bash
lint() {
	cpplint --filter=\
		-build/include_order,\
		-readability/utf8,\
		-whitespace/indent,\
		-whitespace/line_length,\
		-runtime/references\
        $*
}
```

* -build/include\_order - need to ignore because of pre-compiled headers
* -readability/utf8 - I just really want to use Unicode © symbol
* -whitespace/indent - I refuse to put a single space before access modifiers
* -whitespace/line\_length - Tried to enforce this, but these days it's not needed
* -runtime/references - Google doesn't like you to pass objects by reference. I like to sometimes pass objects by reference. Apparently I should use a pointer instead, which is insane to me.

## Todo

Maybe have multiple Turtles?

