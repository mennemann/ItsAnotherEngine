#ifndef Display_H
#define Display_H

#include <string>

#include "core/World.hpp"


void init(std::string window_name, int width, int height);
void display(const World& world);
void destroy();

#endif