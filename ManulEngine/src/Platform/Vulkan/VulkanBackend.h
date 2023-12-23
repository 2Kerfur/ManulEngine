#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include "ManulEngine/Renderer/RendererBackend.h"

#include "VulkanDebug.h"
#include "VulkanDevice.h"
#include "VulkanSurface.h"
#include "VulkanPipline.h"

namespace ManulEngine {

    class VulkanBackend : public RendererBackend
    {
    public:
        virtual bool Init(Vector2Uint windowSize) override;
        virtual void SetWindowSize(Vector2Uint windowSize) override;
        virtual void Render() override;
        virtual void Shutdown() override;
    private:
        bool enableValidationLayers = true;
        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void CreateInstance();
    private:
        VkInstance instance;
        VulkanDevice vulkanDevice;
        VulkanDebug vulkanDebug;
        VulkanSurface vulkanSurface;
        VulkanPipline vulkanPipline;
    };
}