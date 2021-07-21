#include "main.hpp"

float vertices[] = {
     0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
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

    Shader tShader("src/shaders/shader.vs", "src/shaders/shader.fs");

    //Buffer binding
    unsigned int VBO;
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //vertex attrib linking - position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    //vertex attrib linking - color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Sets initial rendering window size and updates if resized
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, GLFW_FB_Size_Callback);
    
    //Main Loop
    while(!glfwWindowShouldClose(window)) {
        //Process Inputs
        glfwProcessInput(window);

        //Actual Rendering
        tShader.use();
        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue) / 2.0f + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "sColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
 