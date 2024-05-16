#ifndef Shapes_H
#define Shapes_H

#include <cmath>
#include <vector>

#include "core/Shape.hpp"
#include "types/Color.hpp"
#include "types/Vec3.hpp"

using namespace std;

class Sphere : public Shape {
   public:
    double radius;

    Sphere(Vec3 position, Color color, double radius) : Shape(position, color), radius(radius) {}

    virtual double sdf(Vec3 position) {
        return (this->position - position).length() - this->radius;
    }
};

class RoundBox : public Shape {
   public:
    Vec3 dimensions;
    double radius;

    RoundBox(Vec3 position, Color color, Vec3 dimensions, double radius) : Shape(position, color), dimensions(dimensions), radius(radius) {}

    virtual double sdf(Vec3 position) {
        Vec3 p = this->position - position;

        Vec3 q{abs(p.x), abs(p.y), abs(p.z)};
        q = q - dimensions;

        return (Vec3{max(q.x, 0.0), max(q.y, 0.0), max(q.z, 0.0)}).length() - min(max(q.x, max(q.y, q.z)), 0.0) - radius;
    }
};

class Box : public RoundBox {
   public:
    Box(Vec3 position, Color color, Vec3 dimensions) : RoundBox(position, color, dimensions, 0.0) {}
};

class Test : public Box {
   public:
    Test(Vec3 position, double width, double depth) : Box(position, Color{255, 255, 255}, Vec3{width, 0, depth}) {}

    virtual Color color(Vec3 position) {
        int square_size = 20;
        int mod_x = (int)position.x % square_size;
        int mod_z = (int)position.z % square_size;

        bool darken = false;
        if (abs(mod_x) >= square_size / 2) {
            darken = true;
        } else
            darken = false;
        if (position.x < 0) darken = !darken;

        if (abs(mod_z) >= square_size / 2) {
            darken = !darken;
        }

        if (darken) {
            Color new_c = this->col;
            new_c.r -= 20;
            new_c.g -= 20;
            new_c.b -= 20;
            return new_c;
        } else
            return this->col;
    }
};
#endif