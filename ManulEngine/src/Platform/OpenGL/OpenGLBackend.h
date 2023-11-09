#pragma once
#include "ManulEngine/Core/Math/Math.h"
#include "GLFW/glfw3.h"
#include "OpenGLPrimitives.h"

class OpenGLBackend {
public:
    void processInput(GLFWwindow *window);

    static void DrawQuad();
    static void DrawLine();
    static void Init(uint32_t windowWidht, uint32_t windowHeight);
    static void SetWindowSize(uint32_t windowWidht, uint32_t windowHeigth);
    static void Render();
    static void DrawLine(Vector3 startPos, Vector3 endPos, Vector3Color color);
private:

};

