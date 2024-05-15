#include "types/Vec3.hpp"

#ifndef Light_H
#define Light_H

class Light {
   public:
    Vec3 position;
    Light(Vec3 position) : position(position) {}
};

#endif