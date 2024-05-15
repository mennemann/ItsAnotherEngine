#ifndef Light_H
#define Light_H

#include "types/Vec3.hpp"


class Light {
   public:
    Vec3 position;
    Light(Vec3 position) : position(position) {}
};

#endif