#version 330 core

vec3 camera_position = vec3(0,200,150);
vec3 camera_right = vec3(1,0,0);

vec3 camera_focus = vec3(0,50,400);

vec3 camera_up = normalize(cross(normalize(camera_focus - camera_position),camera_right));

float sdf(vec3 p);

vec3 shoot(vec3 pos, vec3 direction, vec3 camera_position, float render_distance) {
    vec3 position = vec3(pos);
    while(distance(position, camera_position) < render_distance) {
        float free_distance = sdf(position);
        position = position + (direction * free_distance);
        if (free_distance < 0.1) {
            return vec3(1,1,1);
        }
    }
    return vec3(0,0,0);
}


void main() {
    float width = 1080;
    float height = 720;

    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;

    float focal_length = 1000;
    vec3 position = camera_position;

    vec3 camera_front = normalize(cross(camera_right, camera_up));

    vec3 direction = (camera_front * focal_length) + (camera_right * (x - width/2)) + (camera_up * (y - height/2));
    direction = normalize(direction);
    gl_FragColor = vec4(shoot(position, direction, camera_position, 10000), 1);
}