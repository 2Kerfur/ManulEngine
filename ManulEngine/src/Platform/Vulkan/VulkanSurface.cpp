#include "mapch.h"
#include "VulkanSurface.h"
#include "GLFW/glfw3.h"
#include "ManulEngine/Core/Window.h"
#include <iostream>
void VulkanSurface::CreateSurface(VkInstance instance, GLFWwindow* window) {
    if (glfwCreateWindowSurface(instance, &ManulEngine::Window::GetInstatnce(), nullptr, &surface) != VK_SUCCESS)
        M_CORE_ERROR("VULKAN: Failed to create window surface!");
}
