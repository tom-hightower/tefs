#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using namespace glm;

#include "glfw_callbacks.hpp"

GLFWwindow* window;

const int WIDTH = 960;
const int HEIGHT = 540;

int main() {
    std::cout << "Hello, world!\n";
    glfwSetErrorCallback(GLFW_Error_Callback);
    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "Failed to init GLFW\n");
        return -1;
    }
    window = glfwCreateWindow(WIDTH, HEIGHT, "tefs", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD");
        return -1;
    }
    glViewport(0, 0, WIDTH, HEIGHT);
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
 