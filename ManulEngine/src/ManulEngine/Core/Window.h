#pragma once
#include "ManulEngine/Renderer/Renderer.h"
#include <string>
#include "GLFW/glfw3.h"
#include "ManulEngine/Core/Math/Math.h"

namespace ManulEngine {
	class Window
	{
	public:
		Window();
		~Window();

		bool Create(Vector2Uint size, std::string title, bool fullscreen);
		
		void SetSize(int width, int height, bool fullscreen);
		Vector2Uint GetSize();
		void Update();

		static Window& Get() { return *s_Instance; }
		static GLFWwindow& GetInstatnce() { return *windowInstance; }
		
		bool WindowShouldClose() { return windowShouldClose; }
	private:
		static Window* s_Instance;
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		bool windowShouldClose = false;
		static GLFWwindow* windowInstance;
	};
}