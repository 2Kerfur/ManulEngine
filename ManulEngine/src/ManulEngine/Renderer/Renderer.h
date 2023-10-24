#pragma once

#include "Renderer2D.h"
#include "GLFW/glfw3.h"
namespace ManulEngine {
	class Renderer
	{
	public:
		void Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window);
		void Shutdown();
		void Render();

		void OnWindowResize(uint32_t width, uint32_t height);
	private:
		Renderer2D renderer2D;
	};
}