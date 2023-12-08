#include "mapch.h"	
#include "Input.h"

#include "Window.h"

#include <GLFW/glfw3.h>
namespace ManulEngine {

	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto state = glfwGetKey(&Window::GetInstatnce(), static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto state = glfwGetMouseButton(&Window::GetInstatnce(), static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	Vector2 Input::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(&Window::GetInstatnce(), &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

}