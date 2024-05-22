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
    double tran;

    virtual Color color(Vec3 postition) {
        return this->col;
    }

    virtual double reflectance(Vec3 position) {
        return this->refl;
    }

    virtual double transparency(Vec3 position) {
        return this->tran;
    }

    Shape(Vec3 pos, Color color, double reflectance = 0, double transparency = 0) : position(pos), col(color), refl(reflectance), tran(transparency) {}

    virtual double sdf(Vec3 position) {
        return std::numeric_limits<double>::max();
    }
};

#endif