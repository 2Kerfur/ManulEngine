#pragma once
#include "ManulEngine/Renderer/Renderer.h"
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

		static GLFWwindow& GetInstatnce() { return *windowInstance; }
		static void window_size_callback(GLFWwindow* window, int width, int height);

		bool WindowShouldClose() { return windowShouldClose; }
	private:
		bool windowShouldClose = false;
		static GLFWwindow* windowInstance;
	};
}