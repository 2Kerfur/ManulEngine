#pragma once


#include "../Renderer/Renderer.h"
#include <string>
#include "GLFW/glfw3.h"
namespace ManulEngine {
	class Window
	{
	public:
		Window();
		~Window();

		bool Create(int width, int height, std::string title, bool fullscreen);
		
		void SetSize(int width, int height, bool fullscreen);
		void Update();

		bool windowShouldClose = false;
	private:
		GLFWwindow* windowInstance;
		Renderer render;

	};
}