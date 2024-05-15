#include <string>
#ifndef Vec3_T
#define Vec3_T

class Vec3
{
    public:
        double x, y, z;       
        Vec3(double x, double y, double z);
        Vec3 operator + (Vec3 const &obj);
        Vec3 operator - (Vec3 const &obj);
        double operator * (Vec3 const &obj); // Dot Product
        Vec3 operator * (double const &obj); //scale
        Vec3 cross(Vec3 const obj); // Cross product
        Vec3 normalize();
        std::string string();
        double length();
};

#endif