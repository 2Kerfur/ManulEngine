#pragma once

#include "GLFW/glfw3.h"
class OpenGLBackend {
public:
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO, EBO;
    unsigned int shaderProgram;

    void Init(uint32_t windowWidht, uint32_t windowHeight, GLFWwindow* window);
    void OnWindowResize(int windowWidht, int windowHeigth);
    void Render();
private:

};

