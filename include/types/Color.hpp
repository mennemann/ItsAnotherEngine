#ifndef color_t
#define color_t

struct Color {
    int r;
    int g;
    int b;

    void operator*=(double const other) {
        r*=other;
        g*=other;
        b*=other;
    }

    Color operator*(double const other) const {
        return {r*other, g*other, b*other};
    }

    Color operator+(Color const other) const {
        return {r+other.r, g+other.g, b+other.b};
    }
};

#endif