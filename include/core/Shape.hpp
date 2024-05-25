#ifndef Shape_H
#define Shape_H

#include <limits>
#include <string>

#include "types/Vec3.hpp"
#include "types/color.hpp"

class Shape {
   public:
    Vec3 position;

    Color col;
    double refl;
    double tran;

    virtual std::string color(Vec3 postition) {
        return to_glsl_vec3({col.r,col.g,col.b});
    }

    virtual std::string reflectance(Vec3 position) {
        return std::to_string(refl);
    }

    virtual std::string transparency(Vec3 position) {
        return std::to_string(tran);
    }

    Shape(Vec3 pos, Color color, double reflectance = 0, double transparency = 0) : position(pos), col(color), refl(reflectance), tran(transparency) {}

    virtual std::string sdf(Vec3 position) {
        return "";
    }
};

#endif