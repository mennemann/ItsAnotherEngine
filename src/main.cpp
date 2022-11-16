#include "core/World.hpp"
#include "core/Light.hpp"
#include "shapes/BasicShapes.hpp"
#include "output/display.hpp"
#include <iostream>
using namespace std;

int main(void) {
    int width = 1080;
    int height = 720;

    Color bg{0,0,0};
    vector<vector<Color>> img(height, vector<Color>(width, bg));

    int focal_length = 10*width;
    int render_distance = 50000;

    Vec3 camera_position {0,900,-1.0*focal_length};
    Vec3 camera_up {0,1,0.05};
    Vec3 camera_right {1,0,0};

    auto world = new World;

    world->register_object(new Light{Vec3{500, 1000, 100}});

    world->register_object(new Sphere {{Vec3{0,100,400}}, Color {0,255,255}, 100});
    world->register_object(new Test{{Vec3{0,0,400}}, 400, 400});
    
    int frame = 0;
    while(1) {
        camera_up.z = sin((double)frame / (double)30)*0.65;
        camera_position.y = sin((double)frame / (double)30)*7000;

        vector<Vec3> camera_data {camera_position, camera_up, camera_right};

        world->render(img, camera_data, focal_length, render_distance);
        display("Yay", img, frame);
        frame++;
        cout << frame << endl;
    }
    
    return 0;
}