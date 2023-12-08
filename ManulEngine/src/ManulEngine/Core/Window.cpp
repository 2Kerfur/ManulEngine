#include "mapch.h"
#include "Window.h"

namespace ManulEngine {
    GLFWwindow* Window::windowInstance = nullptr;
    static Vector2Uint windowSize;
    Window::Window()
    {
        windowShouldClose = false;
    }

    void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
    {
        
        windowSize = { unsigned(width), unsigned(height) };
        Renderer::SetWindowSize({windowSize.x, windowSize.y});
    }

    Window::~Window()
    {
        glfwTerminate();
    }
    
    bool Window::Create(Vector2Uint size, std::string title, bool fullscreen)
    {
        
        windowSize = size;
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

#ifdef __APPLE__ //Пусть будет
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        windowInstance = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
        if (!windowInstance)
        {
            M_CORE_ERROR("GLFW failed to create window");
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(windowInstance);
        glfwSetWindowSizeCallback(windowInstance, WindowSizeCallback);

        if (!Renderer::Init(size, Renderer::OpenGL))
        {
            M_CORE_CRITICAL("Failed to initialize renderer");
            return false;
        }
        
        M_CORE_INFO("Renderer initalized successfully");
        return true;
    }

    void Window::SetSize(int width, int height, bool fullscreen)
    {
        glfwSetWindowSize(windowInstance, width, height); //TODO: поддержка fullscreen
    }

    void Window::Update()
    {
        glfwPollEvents();
        windowShouldClose = glfwWindowShouldClose(windowInstance);
        Renderer::Render();
        glfwSwapBuffers(windowInstance);
    }
    inline Vector2Uint Window::GetWindowSize()
    {
        return windowSize;
    }
    inline void Window::SetWindowSize(Vector2Uint size)
    {
        windowSize = size;
    }
}