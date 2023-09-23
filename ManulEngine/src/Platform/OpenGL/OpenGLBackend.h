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
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
    void Init(int windowWidht, int windowHeight, GLFWwindow* window);
    void OnWindowResize(int windowWidht, int windowHeigth);
    void Render();
private:

};

