#include "Renderer.h"
#include "../Core/Logger.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    
}

void Renderer::Init(int windowWidht, int windowHegiht, GLFWwindow* window)
{
    //vulkanBackend.Init(windowWidht, windowHegiht, window);
    openGlBackend.Init(windowWidht, windowHegiht, window);
}
void Renderer::Render()
{
    openGlBackend.Render();
    //vulkanBackend.Render();
}
