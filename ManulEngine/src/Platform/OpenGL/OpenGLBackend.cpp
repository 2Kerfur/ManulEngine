#include "glad/glad.h"
#include "OpenGLBackend.h"
#include "ManulEngine/Core/Log.h"
#include "ManulEngine/Core/Application.h"
#include "ManulEngine/Core/Window.h"

#include "ManulEngine/Renderer/Camera.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace ManulEngine {
    static OpenGLBox box;
    static OpenGLLine line;
    static OpenGLModel model;
    
    bool OpenGLBackend::Init(uint32_t windowWidht, uint32_t windowHeight) {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
        const char* glVersion = reinterpret_cast<const char*>(glad_glGetString(GL_VERSION));
        M_CORE_INFO("Graphics API: OpenGL ({})", glVersion);

        const char* graphicsCard = reinterpret_cast<const char*>(glad_glGetString(GL_RENDERER));
        M_CORE_INFO("Graphics card: {}", graphicsCard);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(&Window::GetInstatnce(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        glEnable(GL_DEPTH_TEST);

        //Create everythig in scene
        //box.Create({ 0, 0, 0 }, { 3, 3 });
        //line.Create({ 0, 0, 0 }, { 3, 3 });
        model.Create();


        //line.Bind(EBO, VAO, VBO);
        //box.Bind(EBO, VAO, VBO);
        return true;
    }

    void OpenGLBackend::SetWindowSize(uint32_t windowWidht, uint32_t windowHeight)
    {
        glViewport(0, 0, windowWidht, windowHeight);
    }
   
    void OpenGLBackend::Render() {
        glClearColor(0.8f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
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
            logs.push_back("[ERROR] Debug log");
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Clear")) { 
            logs.clear();
        }
        for (std::string log : logs)
        {
            ImGui::TextUnformatted(log.c_str());
        }
        
        
        ImGui::End();
        
        ImGui::Render();

        //line.Bind(EBO, VAO, VBO);
        //line.Draw();
        model.Draw();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        
        //box.Bind(EBO, VAO, VBO);
        //box.Draw();
    }
    void OpenGLBackend::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}