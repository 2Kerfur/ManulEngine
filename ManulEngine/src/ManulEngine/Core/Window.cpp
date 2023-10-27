#include "mapch.h"
#include "Window.h"

namespace ManulEngine {
    GLFWwindow* Window::windowInstance = nullptr;
    Window::Window()
    {
        windowShouldClose = false;
    }

    Window::~Window()
    {
        glfwTerminate();
    }
    
    bool Window::Create(int width, int height, std::string title, bool fullscreen)
    {
        windowShouldClose = false;
        if (!glfwInit())
        {
            M_CORE_ERROR("GLFW failed to initialize");
            return false;
        }
        //TODO: для vulkan api
        //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        windowInstance = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!windowInstance)
        {
            M_CORE_ERROR("GLFW failed to create window");
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(windowInstance);
        
        if (!Renderer::Init(width, height))
        {
            M_CORE_CRITICAL("Failed to initialize renderer");
            return false;
        }
        
        M_CORE_INFO("Renderer initalized successfully");
        return true;
    }

    void Window::SetSize(int width, int height, bool fullscreen)
    {
        
    }

    void Window::Update()
    {
        windowShouldClose = glfwWindowShouldClose(windowInstance);
        if (windowShouldClose)
        {
            M_CORE_INFO("IH");
        }
        Renderer::Render();
        glfwSwapBuffers(windowInstance);
        glfwPollEvents();
    }
}