#include "core/World.hpp"
#include "core/Light.hpp"
#include "types/Color.hpp"
#include "types/Vec3.hpp"
#include "core/Shape.hpp"
#include "output/display.hpp"
#include <iostream>
#include <math.h>
using namespace std;









int main(void) {
    int width = 1080;
    int height = 720;

    init("HeeHee", width, height);
    
    World w;

    w.add(new Light{{0, 150, 400}});
    auto s1 = new Shape({0,0,400},{0,0,1});
    w.add(s1);

    Vec3 camera_position = Vec3(0,200,150);
    Vec3 camera_right = Vec3(1,0,0);

    Vec3 camera_focus = Vec3(0,0,400);
    Vec3 camera_up = ((camera_focus-camera_position).cross(camera_right)).normalize();


    camera_data camera {
        camera_position,
        camera_up,
        camera_right,
        1000,
        4000
    };


    int frame = 10;
    while(1) {       
        display(w, camera);

        s1->position.y = 10.0*sin(frame/10.0);

        frame++;
        cout << frame << endl;

        if (frame > 500) break;
    }

    destroy();
    return 0;
}