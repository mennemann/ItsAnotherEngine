#ifndef Shape_H
#define Shape_H

#include <limits>
#include <string>
#include <vector>

#include "types/Vec3.hpp"
#include "types/color.hpp"

class Shape {
   public:
    virtual std::string sdf() = 0;
    virtual std::string color() = 0;
    virtual std::string reflectance() = 0;
    virtual std::string transparency() = 0;

    virtual std::vector<std::string> helpers() {
        return {};
    }
};

#endif