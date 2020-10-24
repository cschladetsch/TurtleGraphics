#pragma once

#include <cmath>

namespace TurtleGraphics {

constexpr float float_epsilon = 0.001f;
constexpr float double_epsilon = 0.00001f;

inline bool ApproxEqual(float a, float b) {
    return fabs(a - b) < float_epsilon;
}

inline bool ApproxEqual(double a, double b) {
    return fabs(a - static_cast<long double>(b)) < double_epsilon;
}

inline int Round(const float x) {
    return x < 0 ? static_cast<int>(x - 0.5f) : static_cast<int>(x + 0.5f);
}

template <typename Ty>
Ty Clamp(const Ty x, Ty min, Ty max) {
    return x < min ? min : x > max ? max : x;
}

}  // namespace TurtleGraphics
