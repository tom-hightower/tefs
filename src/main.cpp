#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using namespace glm;

#include "glfw_funcs.hpp"

GLFWwindow* window;

const int WIDTH = 960;
const int HEIGHT = 540;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

float vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main() {
    std::cout << "Hello, world!\n";
    //GLFW Setup
    glfwSetErrorCallback(GLFW_Error_Callback);
    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "Failed to init GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "tefs - VT", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //GLAD Setup
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD");
        return -1;
    }

    //Buffer binding
    unsigned int VBO;
    unsigned int VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    //vertex shader setup
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int SC_success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &SC_success);
    if(!SC_success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //fragment shader setup
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &SC_success);
    if(!SC_success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //element buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &SC_success);
    if(!SC_success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //vertex attrib linking
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    //shader cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //Sets initial rendering window size and updates if resized
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, GLFW_FB_Size_Callback);
    
    //Main Loop
    while(!glfwWindowShouldClose(window)) {
        //Process Inputs
        glfwProcessInput(window);

        //Actual Rendering
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Events and Buffer Swap
        glfwPollEvents();
        glfwSwapBuffers(window);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    //exit
    glfwTerminate();
    return 0;
}
 