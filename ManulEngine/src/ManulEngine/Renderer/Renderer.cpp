#include "mapch.h"
#include "Renderer.h"
#include "RendererBackend.h"
#include "ManulEngine/Core/Application.h"

#include "Platform/OpenGL/OpenGLBackend.h"
#include "ManulEngine/Core/Log.h"
namespace ManulEngine {
    RendererBackend* Renderer::backend = nullptr;
    bool Renderer::Init(uint32_t windowWidht, uint32_t windowHegiht, GraphicsAPI api)
    {
        switch (api)
        {
        case Renderer::OpenGL:
            backend = dynamic_cast<RendererBackend*>(new OpenGLBackend());
            if (backend->Init(windowWidht, windowHegiht)) 
            
            return true;
        case Renderer::Vulkan:
            M_CORE_CRITICAL("Vulkan not supported");
            break;
        case Renderer::DirectX:
            M_CORE_CRITICAL("DirectX not supported");
            break;
        default:
            M_CORE_ERROR("No graphics api selected");
            break;
        }
        return false;
    }
    void Renderer::Render()
    {
        backend->Render();
    }

    void Renderer::Shutdown()
    {
        backend->Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {

    }
}