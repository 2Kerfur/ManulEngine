#pragma once
#include "../../Platform/Vulkan/VulkanBackend.h"
#include "GLFW/glfw3.h"
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(int windowWidht, int windowHegiht, GLFWwindow* window);
	void Render();
private:
    VulkanBackend vulkanBackend;
    
};