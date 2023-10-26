#include "mapch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "ManulEngine/Core/Application.h" 
namespace ManulEngine {
    bool Renderer::Init(uint32_t windowWidht, uint32_t windowHegiht)
    {
        Renderer2D::Init(windowWidht, windowHegiht);
        return true;
    }
    void Renderer::Render()
    {
        Renderer2D::Render();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {

    }
}