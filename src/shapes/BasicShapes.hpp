#include "../core/Shape.hpp"
#include "../types/Vec3.hpp"
#include "../types/color.hpp"
#include <cmath>
#include <vector>

using namespace std;
#ifndef Shapes_H
#define Shapes_H

class Sphere: public Shape
{
    public:
        double radius;

        Sphere(vector<Vec3> vertices, Color color, double radius) : Shape(vertices, color) {
            this->radius = radius;
        }

        virtual double sdf(Vec3 position) {
            return (this->vertices[0] - position).length() - this->radius; 
        }
};

class Plane: public Shape
{
    public:
        Vec3 normal {0,0,0};

        Plane(vector<Vec3> vertices, Color color, Vec3 normal) : Shape(vertices, color) {
            this->normal = normal.normalize();
        }

        virtual double sdf(Vec3 position) {
            int h = 0;
            return (normal*(position - this->vertices[0]) + h);
        }

        virtual Color color(Vec3 position) {
            int mod_x = (int)position.x % 700;
            int mod_z = (int)position.z % 700;

            bool darken = false;
            if (abs(mod_x) > 350) {
                darken = true;
            } else darken = false;
            if (position.x < 0) darken = !darken;

            if (abs(mod_z) > 350) {
                darken = !darken;
            }


            if (darken) {
                Color new_c = this->col;
                new_c.r -= 20;
                new_c.g -= 20;
                new_c.b -= 20; 
                return new_c;
            } else return this->col;
        }
        
};


class TriPrism: public Shape
{
    public:
        Vec3 dimensions {0,0,0};
        
        TriPrism(vector<Vec3> vertices, Color color, Vec3 dimensions) : Shape(vertices, color) {
            this->dimensions = dimensions;
        }

        virtual double sdf(Vec3 position) {
            Vec3 p = this->vertices[0] - position;
            Vec3 q {abs(p.x),abs(p.y),abs(p.z)};

            return max(q.z-dimensions.y,max(q.x*0.866025+p.y*0.5,-p.y)-dimensions.x*0.5);
        }
};


class Octahedron: public Shape
{
    public:
        double radius;

        Octahedron(vector<Vec3> vertices, Color color, double radius) : Shape(vertices, color) {
            this->radius = radius;
        }

        virtual double sdf(Vec3 position) {
            Vec3 p = (this->vertices[0] - position);
            p = Vec3{abs(p.x),abs(p.y),abs(p.z)};
            return (p.x+p.y+p.z-this->radius)*0.57735027; 
        }
};

class RoundBox: public Shape
{
    public:
        Vec3 dimensions{0,0,0};
        double radius;

        RoundBox(vector<Vec3> vertices, Color color, Vec3 dimensions, double radius) : Shape(vertices, color) {
            this->dimensions = dimensions;
            this->radius = radius;
        }

        virtual double sdf(Vec3 position) {
            Vec3 p = this->vertices[0] - position;

            Vec3 q {abs(p.x),abs(p.y),abs(p.z)};
            q = q - dimensions;
            
            return (Vec3 {max(q.x,0.0),max(q.y,0.0),max(q.z,0.0)}).length() -  min(max(q.x,max(q.y,q.z)),0.0) - radius;
        }
};

class Box: public RoundBox
{
    public:
        Box(vector<Vec3> vertices, Color color, Vec3 dimensions): RoundBox(vertices, color, dimensions, 0.0) {}
};

class Test: public Box
{
    public:
        Test(vector<Vec3> vertices, double width, double depth): Box(vertices, Color{255,255,255}, Vec3{width, 0, depth}){

        }

        virtual Color color(Vec3 position) {
            int square_size = 100;
            int mod_x = (int)position.x % square_size;
            int mod_z = (int)position.z % square_size;

            bool darken = false;
            if (abs(mod_x) > square_size/2) {
                darken = true;
            } else darken = false;
            if (position.x < 0) darken = !darken;

            if (abs(mod_z) > square_size/2) {
                darken = !darken;
            }


            if (darken) {
                Color new_c = this->col;
                new_c.r -= 20;
                new_c.g -= 20;
                new_c.b -= 20; 
                return new_c;
            } else return this->col;
        }

};
#endif