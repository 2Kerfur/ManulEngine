#include "mapch.h"
#include "ImguiLayer.h"
#include "ManulEngine/Core/Window.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
namespace ManulEngine {
    int ImguiLayer::Init(Renderer::GraphicsAPI api)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

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
        //ImGui::ShowDemoWindow();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::Begin("Stats");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        ImGui::Begin("Console");
        if (ImGui::SmallButton("Add Debug Error")) {
            //logs.push_back("[ERROR] Debug log");
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Clear")) {
            //logs.clear();
        }
        //for (std::string log : logs)
        //{
        //    ImGui::TextUnformatted(log.c_str());
        //}

        ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImguiLayer::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}