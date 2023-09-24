#include "Renderer.h"

void Renderer::Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window)
{
    Renderer2D::Init(windowWidht, windowHegiht, window);

}
void Renderer::Render()
{
    Renderer2D::Render();
}

void Renderer::Shutdown() {
    Renderer2D::Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {

}
