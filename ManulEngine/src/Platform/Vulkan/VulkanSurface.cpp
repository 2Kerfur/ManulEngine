
#include "VulkanSurface.h"
#include "GLFW/glfw3.h"

#include <iostream>
void VulkanSurface::createSurface(VkInstance instance, GLFWwindow* window) {

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        std::cout << "failed to create window surface!\n";
    }
}
