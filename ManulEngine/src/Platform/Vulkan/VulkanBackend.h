#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include "VulkanDebug.h"
#include "VulkanDevice.h"
#include "VulkanSurface.h"
#include "VulkanPipline.h"

class VulkanBackend
{
public:
	void Init(int windowWidht, int windowHeight, GLFWwindow* window);
    void Render();
	void OnWindowResize(int windowWidht, int windowHeigth);
private:
    bool enableValidationLayers = true;
    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);



    void CreateInstance();
    VkInstance instance;

    VulkanDevice vulkanDevice;
    VulkanDebug vulkanDebug;
    VulkanSurface vulkanSurface;
    VulkanPipline vulkanPipline;

};