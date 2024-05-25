#include "core/World.hpp"

#include <vector>
#include <string>

#include "types/Color.hpp"
#include "types/Vec3.hpp"


void World::add(Shape* shape) {
    shapes.push_back(shape);
}

void World::add(Light* light) {
    lights.push_back(light);
}

std::string World::sdf() {
    return "";
}