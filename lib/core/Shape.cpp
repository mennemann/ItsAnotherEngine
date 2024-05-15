#include "core/Shape.hpp"

#include "types/Vec3.hpp"
#include "types/color.hpp"

#include <limits>
#include <vector>


using namespace std;

Shape::Shape(vector<Vec3> vertices, Color color) {
    this->vertices = vertices;
    this->col = color;
}

double Shape::sdf(Vec3 position) { 
    return numeric_limits<double>::max();
}

Color Shape::color(Vec3 position) {
    return this->col;
}