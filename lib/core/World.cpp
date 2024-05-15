#include "core/World.hpp"
#include "types/Vec3.hpp"
#include "types/Color.hpp"

#include <limits>
#include <thread>
#include <vector>
#include <cmath>

using namespace std;


void World::add(Shape* shape){
    shapes.push_back(shape);
}

void World::add(Light* light) {
    lights.push_back(light);
}

double World::distance(Vec3 p, Shape* &CLOSEST) {
    double min = numeric_limits<double>::max();
    
    for (int i = 0; (long unsigned int)i < shapes.size(); i++) {
        double dist = shapes[i]->sdf(p);

        if (dist < min){
            min = dist;
            CLOSEST = shapes[i];
        }
    }
    
    return min;
}


Color World::get_pixel(int x, int y, int width, int height, Vec3 camera_position, Vec3 camera_up, Vec3 camera_right, int focal_length, int render_distance){
    camera_up = camera_up.normalize();
    camera_right = camera_right.normalize();
    
    Vec3 camera_front = camera_right.cross(camera_up).normalize();

    Vec3 march_direction = (camera_front * focal_length) + (camera_right*(x - width/2)) + (camera_up*(y - height/2));
    Vec3 march_position = camera_position;

    march_direction = march_direction.normalize();

    Shape* RESULT_HANDLE = NULL;
    bool hit = false;
    while (((march_position - camera_position).length() < render_distance)) {
        double free_distance = World::distance(march_position, RESULT_HANDLE);
        march_position = march_position + (march_direction*free_distance);
        if(free_distance < 0.5) {
            hit = true;
            break;
        }
    }

    if (hit) {
        Color res = RESULT_HANDLE->color(march_position);

        double brightness = 1.0;
        for (auto const &light: lights) {
            brightness = surface_brightness(march_position, *light)*shadow_brightness(march_position, *light);
        }

        double elevation = 0.2;
        brightness = (brightness+elevation)/(1.0+elevation);
        
        res.r *= brightness;
        res.g *= brightness;
        res.b *= brightness;

        return res;
    } else return Color{r:0, g:0, b:0};
}

void World::render_rows(int rows, int offset, vector<vector<Color>> &img, vector<Vec3> camera_data, int focal_length, int render_distance) {
    for (int y = offset; y < offset+rows; y++){
        for (int x = 0; (long unsigned int)x < img[0].size(); x++){
            img[y][x] = get_pixel(x,y,img[0].size(),img.size(), camera_data[0], camera_data[1], camera_data[2], focal_length, render_distance);
        }
    }
}

void World::render(vector<vector<Color>> &img, vector<Vec3> camera_data, int focal_length, int render_distance){
    int rows = img.size();
    int thread_c = 16;

    int block_size = rows/thread_c;

    vector<thread> threads;
    for (int i = 0; i < thread_c; i++) {
        threads.push_back(thread(&World::render_rows, this, 
        block_size,block_size*i, ref(img), 
        camera_data, 
        focal_length, render_distance));
    }

    for (thread& th : threads) th.join();
}

Vec3 World::estimateNormal(Vec3 p) {
    double EPSILON = 0.01;
    Shape* RES = NULL;
    Vec3 normal{
        World::distance(Vec3{p.x + EPSILON, p.y, p.z}, RES) - World::distance(Vec3{p.x - EPSILON, p.y, p.z}, RES),
        World::distance(Vec3{p.x, p.y + EPSILON, p.z}, RES) - World::distance(Vec3{p.x, p.y - EPSILON, p.z}, RES),
        World::distance(Vec3{p.x, p.y, p.z  + EPSILON}, RES) - World::distance(Vec3{p.x, p.y, p.z - EPSILON}, RES)
    };
    return normal.normalize();
}

double World::surface_brightness(Vec3 p, Light l){
    return 1-(estimateNormal(p)*(p-l.position).normalize()+1)/2;
}

double World::shadow_brightness(Vec3 p, Light l){
    Vec3 shadow_direction = (l.position-p).normalize();

    Shape* RESULT_HANDLE = NULL;
    
    p = p+estimateNormal(p);

    double k=16.0;
    double res = 1.0;
    double ph = 1e20;
    
    for (double t = 0.0; t<(l.position-p).length();) {
        double h = World::distance(p+shadow_direction*t, RESULT_HANDLE);
        if (0.05>h) return 0.0;
        double y = h*h/(2.0*ph);
        double d = sqrt(h*h-y*y);
        res = min( res, k*d/max(0.0,t-y) );
        ph = h;
        t += h;
    }

    return res;
}