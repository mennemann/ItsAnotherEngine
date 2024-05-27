#include "core/World.hpp"
#include "core/Light.hpp"
#include "types/Color.hpp"
#include "types/Vec3.hpp"
#include "core/Shape.hpp"
#include "shapes/BasicShapes.hpp"
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

    auto box = new RoundBox({0,50,440},{1,0.2,0.2},{20,20,20},5);
    auto sphere = new Sphere({0,40,400},{0.2,0.9,0.5},20);
    auto plane = new Plane({0,1,0},20);
    
    auto mo = new MeltingObject(sphere, box,30);


    w.add(mo);
    w.add(plane);


    camera_data camera {
        {0,200,150},
        {0,0,0},
        {1,0,0},
        1000,
        4000
    };



    auto start = std::chrono::high_resolution_clock::now();

    int frame = 0;
    while(frame < 1000) {
        camera.position.y = 200*abs(cos((double)frame/100.0));
        camera.up = ((box->p-camera.position).cross(camera.right)).normalize();

        display(w, camera);

        sphere->p.x = 40.0*sin((double)frame/10.0);
        sphere->p.z = 40.0*cos((double)frame/10.0)+400;

        frame++;
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto s = std::chrono::duration_cast<std::chrono::seconds>(end-start);
    std::cout << s.count() << "s\n";
    std::cout << 1000.0/s.count() << " fps\n";

    destroy();
    return 0;
}