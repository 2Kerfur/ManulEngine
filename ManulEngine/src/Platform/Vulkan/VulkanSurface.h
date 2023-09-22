#pragma once
#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"

class VulkanSurface {

public:
    void createSurface(VkInstance instance, GLFWwindow* window);
    VkSurfaceKHR getSurface() {return surface;}
private:
    VkSurfaceKHR surface;
};

