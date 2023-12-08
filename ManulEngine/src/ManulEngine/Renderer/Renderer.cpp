#include "mapch.h"
#include "Renderer.h"
#include "RendererBackend.h"
#include "ManulEngine/Core/Application.h"

#include "Platform/OpenGL/OpenGLBackend.h"
#include "ManulEngine/Core/Log.h"
namespace ManulEngine {
    RendererBackend* Renderer::backend = nullptr;
    bool Renderer::Init(Vector2Uint windowSize, GraphicsAPI api)
    {
        switch (api)
        {
        case Renderer::OpenGL:
            backend = dynamic_cast<RendererBackend*>(new OpenGLBackend());
            if (backend->Init(windowSize))
            return true;
        case Renderer::Vulkan:
            M_CORE_CRITICAL("Vulkan not supported");
            break;
        case Renderer::DirectX:
            M_CORE_CRITICAL("DirectX not supported");
            break;
        default:
            M_CORE_ERROR("Graphics api not supported");
            break;
        }
        return false;
    }
    void Renderer::SetWindowSize(Vector2Uint windowSize)
    {
        backend->SetWindowSize(windowSize);
    }
    void Renderer::Render()
    {
        backend->Render();
    }

    void Renderer::Shutdown()
    {
        backend->Shutdown();
    }
}