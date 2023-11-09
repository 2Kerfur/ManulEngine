#include "mapch.h"
#include "Renderer.h"
#include "RendererBackend.h"
#include "ManulEngine/Core/Application.h" 
namespace ManulEngine {
    bool Renderer::Init(uint32_t windowWidht, uint32_t windowHegiht)
    {
        RendererBackend::Init(windowWidht, windowHegiht);
        return true;
    }
    void Renderer::Render()
    {
        RendererBackend::Render();
    }

    void Renderer::Shutdown()
    {
        RendererBackend::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {

    }
}