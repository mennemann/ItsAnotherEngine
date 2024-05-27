#ifndef BasicShapes_H
#define BasicShapes_H

#include <string>
#include <sstream>
#include <iostream>

#include "core/Shape.hpp"
#include "types/Color.hpp"
#include "types/Vec3.hpp"

class BasicShape : public Shape {
   public:
    Vec3 p;
    Color c;
    double r;
    double t;

    virtual std::string sdf() {
        return "0";
    }

    virtual std::string color() {
        return "return " + to_glsl_vec3({c.r,c.g,c.b}) + ";";
    }

    virtual std::string reflectance() {
        return std::to_string(r);
    }

    virtual std::string transparency() {
        return std::to_string(t);
    }

    BasicShape(Vec3 position, Color color = {1,1,1}, double reflectance = 0, double transparency = 0) : p(position), c(color), r(reflectance), t(transparency) {}
};


class Sphere : public BasicShape {
   public:
    double radius;


    virtual std::string sdf() {
        return "return distance(p," + to_glsl_vec3(p) + ") - " + std::to_string(radius) + ";";
    }

    Sphere(Vec3 position, Color color, double radius, double reflectance = 0, double transparency = 0) : BasicShape(position, color, reflectance, transparency), radius(radius) {}
};

class RoundBox : public BasicShape {
   public:
    Vec3 dimensions;
    double radius;

    virtual std::string sdf() {
        return "vec3 b = " + to_glsl_vec3(dimensions) + ";float r = " + std::to_string(radius) + ";vec3 q = abs(p-" + to_glsl_vec3(p) + ") - b + r;return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0) - r;";
    }

    RoundBox(Vec3 position, Color color, Vec3 dimensions, double radius, double reflectance = 0, double transparency = 0) : BasicShape(position, color, reflectance, transparency), dimensions(dimensions), radius(radius) {}
};

class Plane : public BasicShape {
    public:
    Vec3 normal;
    double h;

    Plane(Vec3 normal, float h) : BasicShape({0,0,0}), normal(normal), h(h) {}

    virtual std::string sdf() {
        return "return dot(" + to_glsl_vec3(normal) + ",p-" + to_glsl_vec3(p) + ") + " + std::to_string(h) + ";";
    }

    virtual std::string color() {
        return R"(
int square_size = 20;
int mod_x = int(mod(int(p.x),square_size));
int mod_z = int(mod(int(p.z),square_size));

bool darken = abs(mod_x) >= square_size / 2;
if (abs(mod_z) >= square_size / 2) darken = !darken;
if(darken) return vec3(0.8,0.8,0.8);
return vec3(1,1,1);
        )";
    } 
};






class MeltingObject : public Shape {
    public:
    Shape *a, *b;
    double k;

    virtual std::string sdf() {
        return "float a = h0"+addr+"(p); float b = h1"+addr+"(p); float k = " + std::to_string(k) +"; float h = max(k-abs(a-b),0.0)/k;return min(a,b) - h*h*h*k*1.0/6.0;";
    }

    virtual std::string color() {
        return "float a = h0"+addr+"(p); float b = h1"+addr+"(p); float m1 = b/(a+b); float m2 = a/(a+b); return m1*h2" + addr + "(p) + m2*h3" + addr + "(p);";
    }

    virtual std::string reflectance() {
        return "0";
    }

    virtual std::string transparency() {
        return "0";
    }

    virtual std::vector<std::string> helpers() {
        auto h_a = a->helpers();
        auto h_b = b->helpers();
        std::vector<std::string> h;
        h.insert(h.end(), h_a.begin(), h_a.end());
        h.insert(h.end(), h_b.begin(), h_b.end());
        std::vector<std::string> j = {
            "float h0" + addr + "(vec3 p) {" + a->sdf() + "}",
            "float h1" + addr + "(vec3 p) {" + b->sdf() + "}",
            "vec3 h2" + addr + "(vec3 p) {" + a->color() + "}",
            "vec3 h3" + addr + "(vec3 p) {" + b->color() + "}",
        };
        h.insert(h.end(), j.begin(), j.end());
        


        return h;
    }

    MeltingObject(Shape* a, Shape* b, double k = 3) : a(a), b(b), k(k) {
        std::ostringstream address;
        address << (void const *)this;
        addr = address.str(); 
    }
    
    private:
    std::string addr;
};

#endif