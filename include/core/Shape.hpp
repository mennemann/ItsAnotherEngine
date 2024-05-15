#ifndef Shape_H
#define Shape_H

#include <limits>

#include "types/Vec3.hpp"
#include "types/color.hpp"

class Shape {
   public:
    Vec3 position;

    Color col;
    double refl;

    virtual Color color(Vec3 postition) {
        return this->col;
    }

    virtual double reflectance(Vec3 position) {
        return this->refl;
    }

    Shape(Vec3 pos, Color color, double reflectance = 0) : position(pos), col(color), refl(reflectance) {}

    virtual double sdf(Vec3 position) {
        return std::numeric_limits<double>::max();
    }
};

#endif