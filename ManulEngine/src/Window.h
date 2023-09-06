#pragma once


#include "Renderer.h"
#include <string>

#include <GLFW/glfw3.h>
class Window
{
public:
	Window();
	~Window();

	int Create(int width, int height, std::string title, bool fullscreen);
	void CreateConsoleWindow();
	void SetSize(int width, int height, bool fullscreen);
	void Update();

	bool windowShouldClose = false;
private:
	GLFWwindow* windowInstance;
	Renderer render;

};