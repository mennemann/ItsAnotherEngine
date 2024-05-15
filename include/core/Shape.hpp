#include "types/Vec3.hpp"
#include "types/color.hpp"
#include <vector>

#ifndef Shape_H
#define Shape_H

class Shape {
    public:
        std::vector<Vec3> vertices;
        Color col;
        Shape(std::vector<Vec3> vertices, Color color);
        
        virtual double sdf(Vec3 position);
        virtual Color color(Vec3 position);
};

#endif