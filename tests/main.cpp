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










int main(void) {
    int width = 1080;
    int height = 720;

    init("HeeHee", width, height);
    
    World w;

    int frame = 10;
    while(1) {        
        display(w);
        frame++;
        cout << frame << endl;

        if (frame > 500) break;
    }

    destroy();
    return 0;
}