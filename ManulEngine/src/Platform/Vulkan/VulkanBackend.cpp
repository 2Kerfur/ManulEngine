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
        M_CORE_INFO("Vulkan Init Started...");
        CreateInstance();
        vulkanDebug.SetupDebugMessenger(enableValidationLayers, instance);
        vulkanSurface.CreateSurface(instance, &Window::GetInstatnce());
        vulkanDevice.PickPhysicalDevice(instance, vulkanSurface.Get());
        vulkanDevice.CreateLogicalDevice(enableValidationLayers);
        vulkanDevice.CreateSwapChain();
        vulkanDevice.CreateImageViews();
        vulkanDevice.CreateRenderPass();
        vulkanPipline.createGraphicsPipeline(vulkanDevice.GetDevice(),
            vulkanDevice.getSwapChainImageViews(),
            vulkanDevice.swapChainFramebuffers,
            vulkanDevice.getSwapChainExtent(),
            vulkanDevice.getSwapChainImageFormat(),
            vulkanDevice.getRenderPass());
        vulkanPipline.createFramebuffers(vulkanDevice.GetDevice());
        vulkanPipline.createCommandPool(vulkanDevice.GetPhysicalDevice(), vulkanDevice.GetDevice(), vulkanDevice.GetSurface());
        vulkanPipline.createCommandBuffer(vulkanDevice.GetDevice());
        vulkanPipline.createSyncObjects(vulkanDevice.GetDevice());
        return true;
    }

    void VulkanBackend::SetWindowSize(Vector2Uint windowSize)
    {
    }
    void VulkanBackend::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            M_CORE_ERROR("VULKAN: Failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = vulkanDevice.getRenderPass();
        renderPassInfo.framebuffer = vulkanDevice.swapChainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = vulkanDevice.getSwapChainExtent();

        VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vulkanPipline.graphicsPipeline);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)vulkanDevice.getSwapChainExtent().width;
        viewport.height = (float)vulkanDevice.getSwapChainExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = vulkanDevice.getSwapChainExtent();
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        vkCmdDraw(commandBuffer, 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            M_CORE_ERROR("VULKAN: Failed to record command buffer!");
        }
    }
    void VulkanBackend::Render()
    {
        vkWaitForFences(vulkanDevice.GetDevice(), 1, &vulkanPipline.inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(vulkanDevice.GetDevice(), 1, &vulkanPipline.inFlightFence);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(vulkanDevice.GetDevice(), vulkanDevice.getSwapChain(), UINT64_MAX, vulkanPipline.imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer(vulkanPipline.commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
        recordCommandBuffer(vulkanPipline.commandBuffer, imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { vulkanPipline.imageAvailableSemaphore };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &vulkanPipline.commandBuffer;

        VkSemaphore signalSemaphores[] = { vulkanPipline.renderFinishedSemaphore };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(vulkanDevice.getGraphicsQueue(), 1, &submitInfo, vulkanPipline.inFlightFence) != VK_SUCCESS) {
            M_CORE_ERROR("VULKAN: failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { vulkanDevice.getSwapChain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(vulkanDevice.getPresentQueue(), &presentInfo);
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

