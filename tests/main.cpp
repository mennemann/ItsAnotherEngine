#include "core/World.hpp"
#include "core/Light.hpp"
#include "types/Color.hpp"
#include "types/Vec3.hpp"
#include "core/Shape.hpp"
#include "shapes/BasicShapes.hpp"
#include "output/display.hpp"
#include <iostream>
using namespace std;



#define M_PI		3.14159265358979323846

double smin(double a, double b, double k) {
    double h = max(k-abs(a-b),0.0)/k;
    return min(a,b) - h*h*h*k*1/6.0;
}

class MeltingObject: public Shape{
    public:
        Shape* s1;
        Shape* s2;

        MeltingObject(Shape* s1, Shape* s2, double refl) : Shape({0,0,0}, Color{255,0,100}, refl){
            this->s1 = s1;
            this->s2 = s2;
        }

        double sdf(Vec3 p) {
            return smin(s1->sdf(p), s2->sdf(p), 30);
        }

        Color color(Vec3 position){
            double dist_s1 = s1->sdf(position);
            double dist_s2 = s2->sdf(position);

            double mag_s2 = dist_s1 / (dist_s1 + dist_s2);
            double mag_s1 = dist_s2 / (dist_s1 + dist_s2);

            return Color{
                r: (int)((double)mag_s1*s1->color(position).r + (double)mag_s2*s2->color(position).r),
                g: (int)((double)mag_s1*s1->color(position).g + (double)mag_s2*s2->color(position).g),
                b: (int)((double)mag_s1*s1->color(position).b + (double)mag_s2*s2->color(position).b)
            };
        }
};


double tri(double x) {
    return 2.0*abs(2*(x-floor(x+0.5)))-1;
}



void create_scene_tir(World* w) {
    auto box = new RoundBox({0,50,500}, {255,255,255}, {50,50,70},0);
    auto sphere = new Sphere({0,50,700}, {0,0,0}, 30);

    box->tran = 0.5;
    sphere->refl = 0.9;

    w->add(box);
    w->add(sphere);
}



int main(void) {
    int width = 1080;
    int height = 720;

    Color bg{0,0,0};
    vector<vector<Color>> img(height, vector<Color>(width, bg));

    int focal_length = 1000;
    int render_distance = 5000;

    Vec3 camera_position {0,200,150};
    Vec3 camera_right {1,0,0};


    auto world = new World;

    world->add(new Light{Vec3{0, 150, 400}});


    auto b1 = new RoundBox{Vec3{0,50,440}, Color {255,55,55}, Vec3{20,20,20}, 5};
    auto s1 = new Sphere {Vec3{0,40,400}, Color {50, 230, 140}, 20};
    

    auto b2 = new RoundBox{Vec3{0,50,400}, Color {255,255,255}, Vec3{100,50,10}, 0};    
    b2->tran = 0.1;

    auto m1 = new MeltingObject(b1,s1,0);
    m1->refl = 0.4;
    // world->add(m1);
    // // world->add(s1);
    // world->add(b2);
    // world->add(s3);


    create_scene_tir(world);

    world->add(new Test{{Vec3{0,-10,400}}, 400, 400,0.1});

    world->background = {0x87,0xCE,0xEB};
    
    int frame = 10;
    while(1) {
        
        // s1->position.x = sin((double)frame/6.0)*40.0;
        // s1->position.z = (cos((double)frame/6.0)*40.0)+400;

        Vec3 cp = camera_position;
        cp.y *= abs(cos((double)frame/24.0));

        Vec3 camera_up = (s1->position - cp).normalize().cross(camera_right);

        vector<Vec3> camera_data {cp, camera_up, camera_right};

        world->render(img, camera_data, focal_length, render_distance);
        display("Yay", img, frame);
        frame++;
    }
    
    return 0;
}