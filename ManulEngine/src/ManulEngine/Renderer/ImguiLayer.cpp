#include "mapch.h"
#include "ImguiLayer.h"
#include "ManulEngine/Core/Window.h"
#include "ManulEngine/Renderer/Renderer.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
namespace ManulEngine {
    static Renderer::GraphicsAPI graphicsApi;
    int ImguiLayer::Init(Renderer::GraphicsAPI api)
    {
        graphicsApi = api;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        //ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

        ImGui::StyleColorsDark();   
        ImGui_ImplGlfw_InitForOpenGL(&Window::GetInstatnce(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        return true;
    }
    
    void ImguiLayer::Render()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::ShowDemoWindow();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::Begin("Stats");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        switch (graphicsApi) {
            case Renderer::OpenGL: ImGui::Text("Renderer graphics api - OpenGL (Stable)"); break;
            case Renderer::Vulkan: ImGui::Text("Renderer graphics api - Vulkan (Not stable)"); break;
            case Renderer::DirectX: ImGui::Text("Renderer graphics api - DirectX (Not supported)"); break;
        }

        RenderViewport();

        ImGui::Render();
        switch (graphicsApi)
        {
        case Renderer::OpenGL:
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            break;
        case Renderer::Vulkan:
            break;
        case Renderer::DirectX:
            break;
        }
    }
    void ImguiLayer::RenderViewport()
    {
        //ImGui::Begin("Viewport");
        //
        //ImGui::End();
    }
    void ImguiLayer::Shutdown()
    {
        switch (graphicsApi)
        {
        case Renderer::OpenGL:
            ImGui_ImplOpenGL3_Shutdown();
            break;
        case Renderer::Vulkan:
            break;
        case Renderer::DirectX:
            break;
        }
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}