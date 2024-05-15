#include "types/Vec3.hpp"


#ifndef Light_H
#define Light_H

class Light{
    public:
        Vec3 position {0,0,0};
        Light(Vec3 position){
            this->position = position;
        }
};

#endif