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
		void Update();

		static GLFWwindow& GetInstatnce() { return *windowInstance; }

		static inline Vector2Uint GetWindowSize();
		static inline void SetWindowSize(Vector2Uint size);

		bool WindowShouldClose() { return windowShouldClose; }
	private:
		
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		bool windowShouldClose = false;
		static GLFWwindow* windowInstance;
	};
}