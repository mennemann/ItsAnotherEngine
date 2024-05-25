#ifndef Vec3_T
#define Vec3_T

#include <string>

class Vec3 {
   public:
    double x, y, z;
    Vec3(double x, double y, double z);
    Vec3 operator+(Vec3 const &obj);
    Vec3 operator-(Vec3 const &obj);
    double operator*(Vec3 const &obj);  // Dot Product
    Vec3 operator*(double const &obj);  // scale
    Vec3 cross(Vec3 const obj);         // Cross product
    Vec3 normalize();
    std::string string();
    double length();
};

Vec3 reflect(Vec3 r, Vec3 n);
Vec3 refract(Vec3 r, Vec3 n, double k1, double k2);

std::string to_glsl_vec3(Vec3 p) {
    return "vec3(" + to_string(p.x) + "," + to_string(p.y) + "," + to_string(p.z) + ")";
}

#endif