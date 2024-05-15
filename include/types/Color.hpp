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
};

#endif