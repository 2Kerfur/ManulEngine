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
    //void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    //{
    //    glViewport(0, 0, width, height); //TODO: Перенести в renderer   
    //}

    //static OpenGLBox box;
    //static OpenGLLine line;

    
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
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(&Window::GetInstatnce(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glEnable(GL_DEPTH_TEST);

        //Create everythig in scene
        //box.Create({ 0, 0, 0 }, { 3, 3 });
        //line.Create({ 0, 0, 0 }, { 3, 3 });



        //line.Bind(EBO, VAO, VBO);
        //box.Bind(EBO, VAO, VBO);
        return true;
    }

    void OpenGLBackend::Render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Stats");                          // Create a window called "Hello, world!" and append into it. 
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        ImGui::Render();
        glClearColor(0.8f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //ImGui::UpdatePlatformWindows();
        //ImGui::RenderPlatformWindowsDefault();



        //ImGui::UpdatePlatformWindows();
        //ImGui::RenderPlatformWindowsDefault();
        //line.Bind(EBO, VAO, VBO);
         //line.Draw();
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