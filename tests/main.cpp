#include "core/World.hpp"
#include "core/Light.hpp"
#include "core/Shape.hpp"
#include "shapes/BasicShapes.hpp"
#include "output/display.hpp"
#include <iostream>
using namespace std;

double smin(double a, double b, double k) {
    double h = max(k-abs(a-b),0.0)/k;
    return min(a,b) - h*h*h*k*1/6.0;
}

class MeltingObject: public Shape{
    public:
        Shape* s1;
        Shape* s2;

        MeltingObject(Shape* s1, Shape* s2) : Shape({Vec3{0,0,0}}, Color{255,0,100}){
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


    auto b1 = new RoundBox{{Vec3{0,25,440}}, Color {255,55,55}, Vec3{20,50,20}, 5};
    auto s1 = new Sphere {{Vec3{0,40,400}}, Color {50, 230, 140}, 20};

    auto m1 = new MeltingObject(b1,s1);
    world->add(m1);

    world->add(new Test{{Vec3{0,0,400}}, 400, 400});

    Vec3 camera_up = (s1->vertices[0] - camera_position).normalize().cross(camera_right);
    
    int frame = 0;
    while(1) {
        
        m1->s2->vertices[0].x = sin((double)frame/6.0)*40.0;
        m1->s2->vertices[0].z = (cos((double)frame/6.0)*40.0)+400;

        vector<Vec3> camera_data {camera_position, camera_up, camera_right};

        world->render(img, camera_data, focal_length, render_distance);
        display("Yay", img, frame);
        //fileout("render.avi", img, frame, 400, 15);
        frame++;
        cout << frame << endl;
    }
    
    return 0;
}