#pragma once
#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include <optional>
#include <vector>

class VulkanDevice
{
public:
    void PickPhysicalDevice(VkInstance instance, VkSurfaceKHR vk_surface);
    void CreateLogicalDevice(bool enableValidationLayers);
    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();

    VkDevice GetDevice() {return device;}
    VkPhysicalDevice GetPhysicalDevice() {return physicalDevice;}
    VkSurfaceKHR GetSurface() {return surface;}
    std::vector<VkImageView>& getSwapChainImageViews(){return swapChainImageViews;}
    std::vector<VkFramebuffer>& getSwapChainFramebuffers(){return swapChainFramebuffers;}
    VkExtent2D getSwapChainExtent(){return swapChainExtent; }
private:
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkRenderPass renderPass;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    }; //TODO: Сейчас deviceExtensions продублированны в VulkanBackend нужно исправить

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};