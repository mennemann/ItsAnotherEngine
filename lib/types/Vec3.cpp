#include "types/Vec3.hpp"
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

Vec3::Vec3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::operator + (Vec3 const &obj){
    return Vec3(this->x+obj.x, this->y+obj.y, this->z+obj.z);
}

Vec3 Vec3::operator - (Vec3 const &obj){
    return Vec3(x-obj.x, this->y-obj.y, this->z-obj.z);
}

double Vec3::operator * (Vec3 const &obj) {
    return (x*obj.x) + (y*obj.y) + (z*obj.z);
}

Vec3 Vec3::operator * (double const &obj) {
    return Vec3(x*obj, y*obj, z*obj);
}

Vec3 Vec3::cross(Vec3 const obj) {
    return Vec3 {y*obj.z - z*obj.y, z*obj.x - x*obj.z, x*obj.y - y*obj.x};
}

Vec3 Vec3::normalize() {
    return (*this)*(1/this->length());
}

double Vec3::length() {
    return sqrt(x*x + y*y + z*z);
}

string Vec3::string(){
    std::ostringstream strs;
    strs << "{ " << x << "  " << y << "  " << z << " }";
    return strs.str();
}

Vec3 reflect(Vec3 r, Vec3 n) {
    return r - n*(2*(r*n));
}