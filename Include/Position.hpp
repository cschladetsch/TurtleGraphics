#pragma once
#include <ostream>

namespace T1 {
    struct Position {
        int x = 0;
        int y = 0;

        Position() { }
        Position(int _x, int _y) {
            x = _x;
            y = _y;
        }

        Position(float _x, float _y) {
            x = Round(_x);
            y = Round(_y);
        }

        friend Position operator*(const Position& A, float scalar) {
            return { Round(A.x*scalar), Round(A.y*scalar)};
        }

        friend Position operator+(const Position& A, const Position& B) {
            return {A.x + B.x, A.y + B.y};
        }

        friend std::ostream& operator<<(std::ostream& lhs, const Position& rhs) {
            return lhs << "x=" << rhs.x << ", y=" << rhs.y;
        }

        static int Round(float scalar) {
            return (int)(scalar + 0.0f);
        }
    };

    typedef Position Vector;
}

