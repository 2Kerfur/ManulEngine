#include "Window.h"

#include <windows.h>
#include <iostream>

Window::Window()
{
}

Window::~Window()
{
    glfwTerminate();
}
void Window::CreateConsoleWindow()
{
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
}
int Window::Create(int width, int height, std::string title, bool fullscreen)
{
    if (!glfwInit()) return -1;

    //TODO: для vulkan api
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    windowInstance = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(windowInstance);
    CreateConsoleWindow();

    render.Init(width, height, windowInstance);
    if (!windowInstance)
    {
        glfwTerminate();
        return -1;
    }

    return 0;
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
