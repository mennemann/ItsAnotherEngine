#ifndef World_H
#define World_H

#include <vector>
#include <string>

#include "Light.hpp"
#include "Shape.hpp"
#include "types/Vec3.hpp"

using namespace std;

class World {
   public:
    vector<Shape*> shapes;
    vector<Light*> lights;

    Color background = {0,0,0};

    void add(Shape* shape);
    void add(Light* light);

    string sdf();
};

#endif