// Copyright © 2020 christian@schladetsch.com

#pragma once
#include <ostream>

#include "Config.hpp"

namespace TurtleGraphics {

struct Position {
    float x = 0;
    float y = 0;

    Position() = default;

    Position(float _x, float _y) {
        x = _x;
        y = _y;
    }

    friend Position operator*(const Position& A, float scalar) {
        return { A.x*scalar, A.y*scalar};
    }

    friend Position operator+(const Position& A, const Position& B) {
        return {A.x + B.x, A.y + B.y};
    }

    friend bool operator==(const Position& A, const Position& B) {
        return ApproxEqual(A.x, B.x) && ApproxEqual(A.y, B.y);
    }

    friend std::ostream& operator<<(std::ostream& lhs,
        const Position& rhs) {
        return lhs << "x=" << rhs.x << ", y=" << rhs.y;
    }
};

typedef Position Vector;

}  // namespace TurtleGraphics

