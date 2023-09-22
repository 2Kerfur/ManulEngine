#pragma once
#include "vulkan/vulkan.h"
class VulkanPipline {

public:
    void createGraphicsPipeline(VkDevice device,
                                std::vector<VkImageView>& SwapChainImageViews,
                                std::vector<VkFramebuffer>& SwapChainFramebuffers,
                                VkExtent2D SwapChainExtent);

    void createFramebuffers(VkDevice device);

    void createCommandPool(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface);

    void createCommandBuffer(VkDevice device);

    void createSyncObjects(VkDevice device);
private:
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkExtent2D swapChainExtent;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;

    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
};
