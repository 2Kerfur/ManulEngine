#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include "VulkanDebug.h"
#include "VulkanDevice.h"


class VulkanBackend
{
public:
	VulkanBackend();
	~VulkanBackend();
	void Init(int windowWidht, int windowHeight, GLFWwindow* window);
	
	void OnWindowResize(int windowWidht, int windowHeigth);
	void Render();
private:
	//Window Surface code TODO: Remove to another class
	VkSurfaceKHR surface;


	VulkanDebug vulkanDebug;
    VulkanDevice vulkanDevice;

	VkInstance instance;
	
	std::vector<const char*> getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		return extensions;
	}
	const bool enableValidationLayers = true; //TODO: Create Switch for this
};