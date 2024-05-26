#version 430 core

#define MAX_LIGHTS_N 20
#define width 1080
#define height 720

struct camera_data {
    vec3 position;
    vec3 up;
    vec3 right;
    float focal_length;
    float render_distance;
};

struct lights_data {
    vec3 position[MAX_LIGHTS_N];
    int N;
};

struct shape {
    vec3 color;
    float reflectivity;
    float transparency;
};


out vec4 FragColor;

uniform camera_data camera;
uniform vec3 background;
uniform lights_data lights;


float sdf(vec3 p);
shape closest();

vec3 estimateNormal(vec3 p) {
    float EPSILON = 0.01;

    return normalize(vec3(
        sdf(vec3(p.x + EPSILON, p.y, p.z)) - sdf(vec3(p.x - EPSILON, p.y, p.z)),
        sdf(vec3(p.x, p.y + EPSILON, p.z)) - sdf(vec3(p.x, p.y - EPSILON, p.z)),
        sdf(vec3(p.x, p.y, p.z + EPSILON)) - sdf(vec3(p.x, p.y, p.z - EPSILON))
    ));
}

float surface_brightness(vec3 p, vec3 l) {
    return ( 1 - (dot(estimateNormal(p), normalize(p - l)) + 1) / 2 );
}


vec3 shoot(vec3 position, vec3 direction) {
    while(distance(position, camera.position) < camera.render_distance) {
        float free_distance = sdf(position);
        position += (direction * free_distance);
        if (free_distance < 0.1) {
            vec3 c = closest().color;


            float brightness = 0;
            for (int i = 0; i < lights.N; i++) {
                brightness += surface_brightness(position, lights.position[i]);
            }
            brightness /= lights.N;

            float elevation = 0.2;
            c *= (brightness + elevation) / (1.0 + elevation);

            return c;
        }
    }
    return background;
}


void main() {
    vec3 direction = normalize((normalize(cross(camera.right, camera.up)) * camera.focal_length) + (camera.right * (gl_FragCoord.x - width/2)) + (camera.up * (gl_FragCoord.y - height/2)));
    FragColor = vec4(shoot(camera.position, direction), 1);
}