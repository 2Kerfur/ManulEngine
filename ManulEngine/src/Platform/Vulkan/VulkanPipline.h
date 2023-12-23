#pragma once
#include "vulkan/vulkan.h"
class VulkanPipline {

public:
    void createGraphicsPipeline(VkDevice device,
                                std::vector<VkImageView>& SwapChainImageViews,
                                std::vector<VkFramebuffer>& SwapChainFramebuffers,
                                VkExtent2D SwapChainExtent,
                            VkFormat swapChainImageFormat, 
        VkRenderPass renderPass);

    void createFramebuffers(VkDevice device);

    void createCommandPool(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface);
    void createCommandBuffer(VkDevice device);
    void createRenderPass();
    VkFence inFlightFence;
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    void createSyncObjects(VkDevice device);
    
    VkPipeline graphicsPipeline;
    VkCommandBuffer commandBuffer;
private:
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkExtent2D swapChainExtent;
    VkCommandPool commandPool;
    VkDevice vkDevice;
    
    
    VkFormat vkSwapChainImageFormat;

    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
};
