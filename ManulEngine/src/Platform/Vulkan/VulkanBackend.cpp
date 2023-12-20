#include "mapch.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include "ManulEngine/Core/Window.h"
#include "VulkanBackend.h"

namespace ManulEngine {
    bool VulkanBackend::Init(Vector2Uint windowSize) {
        CreateInstance();
        M_CORE_INFO("Vulkan Init Started");
        vulkanDebug.setupDebugMessenger(enableValidationLayers, instance);
        vulkanSurface.createSurface(instance, &Window::GetInstatnce());
        //vulkanDevice.pickPhysicalDevice(instance, vulkanSurface.getSurface());
        //vulkanDevice.createLogicalDevice(enableValidationLayers, &Window::GetInstatnce());
        //vulkanDevice.createSwapChain();
        //vulkanDevice.createImageViews();
        //vulkanDevice.createRenderPass();
        //vulkanPipline.createGraphicsPipeline(vulkanDevice.GetDevice(),
        //    vulkanDevice.getSwapChainImageViews(),
        //    vulkanDevice.getSwapChainFramebuffers(),
        //    vulkanDevice.getSwapChainExtent());
        //vulkanPipline.createFramebuffers(vulkanDevice.GetDevice());
        //vulkanPipline.createCommandPool(vulkanDevice.GetPhysicalDevice(), vulkanDevice.GetDevice(), vulkanDevice.GetSurface());
        //vulkanPipline.createCommandBuffer(vulkanDevice.GetDevice());
        //vulkanPipline.createSyncObjects(vulkanDevice.GetDevice());
        return true;
    }

    void VulkanBackend::SetWindowSize(Vector2Uint windowSize)
    {
    }
    void VulkanBackend::Render()
    {
    }
    void VulkanBackend::Shutdown()
    {
    }

    bool VulkanBackend::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound) return false;
        }

        return true;
    }
    std::vector<const char*> VulkanBackend::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        return extensions;
    }

    void VulkanBackend::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = VulkanDebug::DebugCallback;
    }
    void VulkanBackend::CreateInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport())
            M_CORE_ERROR("VULKAN: Validation layers requested, but not available!");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "ManulEngine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "ManulEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            M_CORE_ERROR("VULKAN: Failed to create instance!");
    }
}

