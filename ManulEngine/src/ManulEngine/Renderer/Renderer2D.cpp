#include "Renderer2D.h"
#include "RendererBackend.h"

void Renderer2D::Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window) {
    RendererBackend::Init(windowWidht, windowHegiht, window);
}

void Renderer2D::Shutdown() {

}

void Renderer2D::Render() {
    RendererBackend::Render();
}
