// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <ostream>
#include "Math.hpp"

namespace TurtleGraphics {

// Components are in range [-inf..inf], and can be normalised to [0..1]
struct Color
{
    float r = 0;
    float g = 0;
    float b = 0;

    Color() = default;

    Color(const float _r, const float _g, const float _b)
        : r(_r), g(_g), b(_b) { }

    Color Normalise() const {
        return { Normalise(r), Normalise(g), Normalise(b) };
    }

    static float Normalise(const float c) {
        return c - static_cast<float>(static_cast<int>(c + (c < 0 ? -0.5f : 0)));
    }

    friend bool operator==(Color const &A, Color const &B) {
        return ApproxEqual(A.r, B.r) && ApproxEqual(A.g, B.g) && ApproxEqual(A.g, B.g);
    }

    friend std::ostream& operator<<(std::ostream &out, Color const &c) {
        return out << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
    }
};

// Components are in range [0..255]
struct ColorInt {
    int r = 0 , g = 0, b = 0;

    ColorInt() = default;

    explicit ColorInt(Color const &d) {
        const auto n = d.Normalise();
        r = Clamp(Round(n.r*255), 0, 255);
        g = Clamp(Round(n.g*255), 0, 255);
        b = Clamp(Round(n.b*255), 0, 255);;
    }

    ColorInt(int r, int g, int b) {
        this->r = Clamp(r, 0, 255);
        this->g = Clamp(g, 0, 255);
        this->b = Clamp(b, 0, 255);
    }

    friend bool operator==(ColorInt const &A, ColorInt const &B) {
        return A.r == B.r && A.g == B.g && A.b == B.b;
    }
};

}  // namespace TurtleGraphics


