#include "Renderer.h"
#include "../Core/Logger.h"
#include <iostream>
#include "../../Platform/Vulkan/VulkanDebug.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    
}

void Renderer::Init(int windowWidht, int windowHegiht, GLFWwindow* window)
{
    vulkanBackend.Init(windowWidht, windowHegiht, window);
}
void Renderer::Render()
{
    vulkanBackend.Render();
}
