#include "mapch.h"

#include "Window.h"
#include <windows.h>
#include <iostream>

namespace ManulEngine {
    Window::Window()
    {
    }

    Window::~Window()
    {
        glfwTerminate();
    }
    
    bool Window::Create(int width, int height, std::string title, bool fullscreen)
    {
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


        windowInstance = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!windowInstance)
        {
            M_CORE_ERROR("GLFW failed to create window");
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(windowInstance);
        
        if (!render.Init(width, height, windowInstance))
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
        render.Render();
        glfwSwapBuffers(windowInstance);
        glfwPollEvents();
    }
}