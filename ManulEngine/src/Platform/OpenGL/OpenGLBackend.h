#pragma once
#include "ManulEngine/Core/Math/Math.h"
#include "GLFW/glfw3.h"
#include "OpenGLShader.h"
#include "OpenGLPrimitives.h"

class OpenGLBackend {
public:
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO, EBO;
    OpenGLShader shader;
    OpenGLBox box;
    void Init(uint32_t windowWidht, uint32_t windowHeight, GLFWwindow* window);
    void OnWindowResize(int windowWidht, int windowHeigth);
    void Render();
    void DrawLine(Vector3 startPos, Vector3 endPos, Vector3Color color);
private:

};

