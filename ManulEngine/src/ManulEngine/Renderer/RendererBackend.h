//#include "Platform/Vulkan/VulkanBackend.h"
#pragma once
#include "Platform/OpenGL/OpenGLBackend.h"

class RendererBackend {
public:
    void Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window);
    void Shutdown();
    void Render();
    OpenGLBackend openGlBackend;
private:
    //VulkanBackend vulkanBackend;

};
