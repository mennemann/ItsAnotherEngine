#include <vector>

#include "Light.hpp"
#include "Shape.hpp"
#include "types/Vec3.hpp"

using namespace std;

#ifndef World_H
#define World_H

class World {
   public:
    vector<Shape*> shapes;
    vector<Light*> lights;

    void add(Shape* shape);
    void add(Light* light);

    double distance(Vec3 p, Shape*& CLOSEST);

    void render(vector<vector<Color>>& img, vector<Vec3> camera_data, int focal_length, int render_distance);

   private:
    Color shoot(Vec3 position, Vec3 direction, Vec3 camera_position, int render_distance, int n);
    Color get_pixel(int x, int y, int width, int height, Vec3 camera_position, Vec3 camera_up, Vec3 camera_right, int focal_length, int render_distance);
    Vec3 estimateNormal(Vec3 p);
    double surface_brightness(Vec3 p, Light l);
    double shadow_brightness(Vec3 p, Light l);
};

#endif