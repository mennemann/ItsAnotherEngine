#include "core/World.hpp"

#include <cmath>
#include <limits>
#include <thread>
#include <vector>

#include "types/Color.hpp"
#include "types/Vec3.hpp"

using namespace std;


void World::add(Shape* shape) {
    shapes.push_back(shape);
}

void World::add(Light* light) {
    lights.push_back(light);
}

double World::distance(Vec3 p, Shape*& CLOSEST) {
    double min = numeric_limits<double>::max();

    for (int i = 0; (long unsigned int)i < shapes.size(); i++) {
        double dist = shapes[i]->sdf(p);

        if (dist < min) {
            min = dist;
            CLOSEST = shapes[i];
        }
    }

    return min;
}

Color World::shoot(Vec3 position, Vec3 direction, Vec3 camera_position, int render_distance, int n) {
    Shape* RESULT_HANDLE = NULL;

    while (((position - camera_position).length() < render_distance)) {
        double free_distance = World::distance(position, RESULT_HANDLE);
        position = position + (direction * free_distance);
        if (free_distance < 0.1) {
            Color c = RESULT_HANDLE->color(position);

            double brightness = 1.0;
            for (auto const& light : lights) {
                brightness = surface_brightness(position, *light) * shadow_brightness(position, *light);
            }

            double elevation = 0;
            brightness = (brightness + elevation) / (1.0 + elevation);

            c *= brightness;
            return c;
        }
    }

    return Color{0, 0, 0};
}

Color World::get_pixel(int x, int y, int width, int height, Vec3 camera_position, Vec3 camera_up, Vec3 camera_right, int focal_length, int render_distance) {
    camera_up = camera_up.normalize();
    camera_right = camera_right.normalize();

    Vec3 camera_front = camera_right.cross(camera_up).normalize();
    Vec3 march_direction = (camera_front * focal_length) + (camera_right * (x - width / 2)) + (camera_up * (y - height / 2));

    return shoot(camera_position, march_direction.normalize(), camera_position, render_distance, 0);
}

void World::render(vector<vector<Color>>& img, vector<Vec3> camera_data, int focal_length, int render_distance) {
#pragma omp parallel for
    for (int i = 0; i < img.size() * img[0].size(); i++) {
        int x = i % img[0].size();
        int y = i / img[0].size();

        img[y][x] = get_pixel(x, y, img[0].size(), img.size(), camera_data[0], camera_data[1], camera_data[2], focal_length, render_distance);
    }
}

Vec3 World::estimateNormal(Vec3 p) {
    double EPSILON = 0.01;
    Shape* RES = NULL;
    Vec3 normal{
        World::distance(Vec3{p.x + EPSILON, p.y, p.z}, RES) - World::distance(Vec3{p.x - EPSILON, p.y, p.z}, RES),
        World::distance(Vec3{p.x, p.y + EPSILON, p.z}, RES) - World::distance(Vec3{p.x, p.y - EPSILON, p.z}, RES),
        World::distance(Vec3{p.x, p.y, p.z + EPSILON}, RES) - World::distance(Vec3{p.x, p.y, p.z - EPSILON}, RES)};
    return normal.normalize();
}

double World::surface_brightness(Vec3 p, Light l) {
    return 1 - (estimateNormal(p) * (p - l.position).normalize() + 1) / 2;
}

double World::shadow_brightness(Vec3 p, Light l) {
    Vec3 shadow_direction = (l.position - p).normalize();

    Shape* RESULT_HANDLE = NULL;

    p = p + estimateNormal(p);

    double k = 16.0;
    double res = 1.0;
    double ph = 1e20;

    for (double t = 0.0; t < (l.position - p).length();) {
        double h = World::distance(p + shadow_direction * t, RESULT_HANDLE);
        if (0.05 > h) return 0.0;
        double y = h * h / (2.0 * ph);
        double d = sqrt(h * h - y * y);
        res = min(res, k * d / max(0.0, t - y));
        ph = h;
        t += h;
    }

    return res;
}