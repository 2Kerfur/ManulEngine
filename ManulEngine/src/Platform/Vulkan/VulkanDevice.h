#pragma once
#include "vulkan/vulkan.h"
#include <optional>
#include <vector>

class VulkanDevice
{
public:
	void FindDevice(VkInstance instance, VkSurfaceKHR surface);
	const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	int CreateLogicalDevice(VkSurfaceKHR surface);
	void Clear();
private:
	VkDevice device;
	VkQueue graphicsQueue;
    VkQueue presentQueue;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
};