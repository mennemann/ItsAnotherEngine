#ifndef color_t
#define color_t

struct Color {
    double r;
    double g;
    double b;

    void operator*=(double const other) {
        r *= other;
        g *= other;
        b *= other;
    }

    Color operator*(double const other) const {
        return {r * other, g * other, b * other};
    }

    Color operator+(Color const other) const {
        return {r + other.r, g + other.g, b + other.b};
    }
};

#endif