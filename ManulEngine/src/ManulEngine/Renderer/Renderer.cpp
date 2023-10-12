#include "Renderer.h"

void Renderer::Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window)
{
    renderer2D.Init(windowWidht, windowHegiht, window);
}
void Renderer::Render()
{
    renderer2D.Render();
}

void Renderer::Shutdown() 
{
    renderer2D.Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {

}
