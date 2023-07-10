#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include <vector>
#include <vulkan/vulkan.h>
#include "Device.h"

class SwapChain {
public:
    SwapChain(Device* device, VkSurfaceKHR* surface);
    ~SwapChain();

    // Function to initialize swapchain
    void init(uint32_t windowWidth, uint32_t windowHeight);

    // Getters for the swapchain's properties
    VkSwapchainKHR getSwapChain() const { return swapChain; }
    const std::vector<VkImage>& getImages() const { return swapChainImages; }
    const std::vector<VkImageView>& getImageViews() const { return swapChainImageViews; }
    VkFormat getImageFormat() const { return swapChainImageFormat; }
    VkExtent2D getExtent() const { return swapChainExtent; }

private:
    void createSwapChain(uint32_t windowWidth, uint32_t windowHeight);
    void createImageViews();
    void cleanupSwapChain();

    Device* p_device;
    VkSurfaceKHR* p_surface;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
};

#endif // SWAPCHAIN_H

