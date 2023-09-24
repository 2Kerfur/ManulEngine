#pragma once

#include "Renderer2D.h"
#include "GLFW/glfw3.h"
class Renderer
{
public:
	static void Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window);
    static void Shutdown();
	static void Render();

    static void OnWindowResize(uint32_t width, uint32_t height);
private:

};