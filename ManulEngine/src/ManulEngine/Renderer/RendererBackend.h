//#include "Platform/Vulkan/VulkanBackend.h"
#include "Platform/OpenGL/OpenGLBackend.h"

class RendererBackend {
public:
    static void Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window);
    static void Shutdown();
    static void Render();
    //static OpenGLBackend openGlBackend;
private:
    //VulkanBackend vulkanBackend;

};
