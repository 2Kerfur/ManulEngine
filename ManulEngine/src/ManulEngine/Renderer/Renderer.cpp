#include "mapch.h"
#include "Renderer.h"
#include "RendererBackend.h"
#include "ManulEngine/Core/Application.h"

#include "Platform/OpenGL/OpenGLBackend.h"
#include "Platform/Vulkan/VulkanBackend.h"
#include "ManulEngine/Core/Log.h"
#include "ImguiLayer.h"

namespace ManulEngine {
    RendererBackend* Renderer::backend = nullptr;
    bool Renderer::Init(Vector2Uint windowSize, GraphicsAPI api)
    {
        switch (api)
        {
        case Renderer::OpenGL:
            backend = dynamic_cast<RendererBackend*>(new OpenGLBackend());
            if (!backend->Init(windowSize)) return false;
            ImguiLayer::Init(Renderer::OpenGL);
            break;
        case Renderer::Vulkan:
            backend = dynamic_cast<RendererBackend*>(new VulkanBackend());
            if (!backend->Init(windowSize)) return false;
            //ImguiLayer::Init(Renderer::Vulkan);
            break;
        case Renderer::DirectX:
            M_CORE_CRITICAL("DirectX not supported");
            return false;
        default:
            M_CORE_ERROR("Graphics api not supported");
            return false;
        }
        return true;
    }
    void Renderer::SetWindowSize(Vector2Uint windowSize)
    {
        backend->SetWindowSize(windowSize);
    }
    void Renderer::Render()
    {
        backend->Render();
        
        //ImguiLayer::Render();
    }

    void Renderer::Shutdown()
    {
        backend->Shutdown();
        //ImguiLayer::Shutdown();
    }
}