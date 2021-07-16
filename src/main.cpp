#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using namespace glm;

#include "glfw_callbacks.hpp"

GLFWwindow* window;

int main() {
    std::cout << "Hello, world!\n";
    glfwSetErrorCallback(GLFW_Error_Callback);
    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "Failed to init GLFW\n");
        return -1;
    }
    window = glfwCreateWindow(960, 540, "tefs", NULL, NULL);
    while (true) {}
}
