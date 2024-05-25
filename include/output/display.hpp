#ifndef Display_H
#define Display_H

#include <string>
#include "types/Vec3.hpp"

#include "core/World.hpp"

struct camera_data {
    Vec3 position;
    Vec3 up;
    Vec3 right;
    float focal_length;
    float render_distance;
};

void init(std::string window_name, int width, int height);
void display(const World& world, camera_data camera);
void destroy();

#endif