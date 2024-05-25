#include "output/display.hpp"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>


GLFWwindow* window = nullptr;
GLuint VBO, VAO;

unsigned int shaderProgram;





std::string readFile(std::string path) {
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
    return str;
}


// Function to compile shaders and link them into a program
void createShaderBaseProgram() {
    // Vertex Shader source code
    const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

    std::string fragmentShaderSourceString = readFile("shader/render.frag");
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

    int success;
    char infoLog[512];

    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // Check for shader compile errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }



    // Link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);


    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


// Function to initialize GLFW and GLAD
void init(std::string window_name, int width, int height) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Define the viewport dimensions
    glViewport(0, 0, width, height);

    // Set up vertex data and buffers
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    createShaderBaseProgram();
}




unsigned int generateSdfShaderFunction(const World& world) {
    auto r = R"(
float sdf(vec3 p) {
    vec3 q = vec3(20,0,400);
    return distance(q,p) - 10;
}
    )"; 






    
    unsigned int sdfShaderFunction = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sdfShaderFunction, 1, &r, nullptr);
    glCompileShader(sdfShaderFunction);


    return sdfShaderFunction;
}




void display(const World& world, camera_data camera) {
    if (glfwWindowShouldClose(window)) exit(0);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    glClear(GL_COLOR_BUFFER_BIT);



    unsigned int sdfShaderFunction = generateSdfShaderFunction(world);
    glAttachShader(shaderProgram, sdfShaderFunction);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);



    glUniform3f(glGetUniformLocation(shaderProgram, "camera.position"),camera.position.x,camera.position.y,camera.position.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "camera.up"),camera.up.x,camera.up.y,camera.up.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "camera.right"),camera.right.x,camera.right.y,camera.right.z);
    glUniform1f(glGetUniformLocation(shaderProgram, "camera.focal_length"), camera.focal_length);
    glUniform1f(glGetUniformLocation(shaderProgram, "camera.render_distance"), camera.render_distance);



    glDetachShader(shaderProgram, sdfShaderFunction);
    glDeleteShader(sdfShaderFunction);



    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void destroy() {
    // Clean up
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW
    glfwTerminate();
}