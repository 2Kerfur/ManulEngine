#include "Renderer.h"
#include "Logger.h"
#include <iostream>
#include "VK_Renderer/VulkanDebug.h"


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
