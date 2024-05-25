#ifndef World_H
#define World_H

#include <vector>

#include "Light.hpp"
#include "Shape.hpp"
#include "types/Color.hpp"

using namespace std;

class World {
   public:
    Color background = {0,0,0};
    
    vector<Shape*> shapes;
    vector<Light*> lights;

    void add(Shape* shape) {
        shapes.push_back(shape);
    }

    void add(Light* light) {
        lights.push_back(light);
    }
};

#endif