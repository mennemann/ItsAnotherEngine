#ifndef color_t
#define color_t

struct Color {
    float r;
    float g;
    float b;

    void operator*=(double const other) {
        r *= other;
        g *= other;
        b *= other;
    }

    Color operator*(double const other) const {
        return {static_cast<int>(r * other), static_cast<int>(g * other), static_cast<int>(b * other)};
    }

    Color operator+(Color const other) const {
        return {r + other.r, g + other.g, b + other.b};
    }
};

#endif