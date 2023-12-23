#pragma once
#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"

class VulkanSurface {
public:
    void CreateSurface(VkInstance instance, GLFWwindow* window);
    VkSurfaceKHR Get() {return surface;}
private:
    VkSurfaceKHR surface;
};

