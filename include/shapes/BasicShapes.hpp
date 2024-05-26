#ifndef BasicShapes_H
#define BasicShapes_H

#include <string>

#include "core/Shape.hpp"
#include "types/Color.hpp"
#include "types/Vec3.hpp"

class BasicShape : public Shape {
   public:
    Vec3 p;
    Color c;
    double r;
    double t;

    virtual std::string sdf() {
        return "0";
    }

    virtual std::string color() {
        return to_glsl_vec3({c.r,c.g,c.b});
    }

    virtual std::string reflectance() {
        return std::to_string(r);
    }

    virtual std::string transparency() {
        return std::to_string(t);
    }

    BasicShape(Vec3 position, Color color = {1,1,1}, double reflectance = 0, double transparency = 0) : p(position), c(color), r(reflectance), t(transparency) {}
};


class Sphere : public BasicShape {
   public:
    double radius;


    virtual std::string sdf() {
        return "return distance(p," + to_glsl_vec3(p) + ") - " + std::to_string(radius) + ";";
    }

    Sphere(Vec3 position, Color color, double radius, double reflectance = 0, double transparency = 0) : BasicShape(position, color, reflectance, transparency), radius(radius) {}
};

class RoundBox : public BasicShape {
   public:
    Vec3 dimensions;
    double radius;

    virtual std::string sdf() {
        return "vec3 b = " + to_glsl_vec3(dimensions) + ";float r = " + to_string(radius) + ";vec3 q = abs(p-" + to_glsl_vec3(p) + ") - b + r;return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0) - r;";
    }

    RoundBox(Vec3 position, Color color, Vec3 dimensions, double radius, double reflectance = 0, double transparency = 0) : BasicShape(position, color, reflectance, transparency), dimensions(dimensions), radius(radius) {}
};

#endif