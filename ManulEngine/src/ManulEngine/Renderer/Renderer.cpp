#include "mapch.h"
#include "Renderer.h"
#include "ManulEngine/Core/Application.h"
#include "ManulEngine/Core/Log.h"   
namespace ManulEngine {
    bool Renderer::Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window)
    {
        renderer2D.Init(windowWidht, windowHegiht, window);
        return true;
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
}