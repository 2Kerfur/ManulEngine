#pragma once
#include "GLFW/glfw3.h"
#include "RendererBackend.h"

class Renderer2D {
public:
    void Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window);
    void Shutdown();
    void Render();
    RendererBackend rendererBackend;
};
