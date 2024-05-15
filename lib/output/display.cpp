#include "output/display.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include "types/color.hpp"

using namespace std;

GLFWwindow* window = nullptr;
uint8_t* rgbArray;

auto init(int WIDTH, int HEIGHT) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    rgbArray = new uint8_t[WIDTH * HEIGHT * 3];
    return 0;
}


void display(string window_name, vector<vector<Color>>& img, int frame) {
    int width = img[0].size();
    int height = img.size();
    if (window == nullptr) init(width, height);
    glClear(GL_COLOR_BUFFER_BIT);


    for (int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int index = (y*width +x) * 3;
            rgbArray[index] = img[y][x].r;
            rgbArray[index + 1] = img[y][x].g;
            rgbArray[index + 2] = img[y][x].b;
        }
    }

    glRasterPos2i(-1, -1);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, rgbArray);

    glfwSwapBuffers(window);
    glfwPollEvents();
}