#version 430 core

float width = 1080;
float height = 720;

struct camera_data {
    vec3 position;
    vec3 up;
    vec3 right;
    float focal_length;
    float render_distance;
};

struct lights_data {
    vec3 position[10];
    int N;
};


out vec4 FragColor;

uniform camera_data camera;
uniform vec3 background;
uniform lights_data lights;

float sdf(vec3 p);

vec3 shoot(vec3 position, vec3 direction) {
    while(distance(position, camera.position) < camera.render_distance) {
        float free_distance = sdf(position);
        position += (direction * free_distance);
        if (free_distance < 0.1) {
            return vec3(1,1,0);
        }
    }
    return background;
}


void main() {
    vec3 direction = normalize((normalize(cross(camera.right, camera.up)) * camera.focal_length) + (camera.right * (gl_FragCoord.x - width/2)) + (camera.up * (gl_FragCoord.y - height/2)));
    FragColor = vec4(shoot(camera.position, direction), 1);
}