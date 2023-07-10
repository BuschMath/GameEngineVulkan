#include "SwapChain.h"

SwapChain::SwapChain(Device* device, VkSurfaceKHR* surface)
{
    p_device = device;
    p_surface = surface;
}

SwapChain::~SwapChain() {
    cleanupSwapChain();
}

void SwapChain::init(uint32_t windowWidth, uint32_t windowHeight) {
    createSwapChain(windowWidth, windowHeight);
    createImageViews();
}

void SwapChain::createSwapChain(uint32_t windowWidth, uint32_t windowHeight) {
    // Here you'd select suitable swapchain parameters
    // This involves querying the capabilities of the surface and selecting suitable options
    // Then you'd call vkCreateSwapchainKHR to actually create the swapchain
    // This function should also retrieve the swapchain images by calling vkGetSwapchainImagesKHR
    SwapChainSupportDetails swapChainSupport = p_device->querySwapChainSupport(p_device->getPhysicalDevice());

    VkSurfaceFormatKHR surfaceFormat = p_device->chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = p_device->chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = p_device->chooseSwapExtent(swapChainSupport.capabilities);

    // Number of images in the swap chain
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    // Specifying details of the swap chain images
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = *p_surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    // Specify how to handle swap chain images that will be used across multiple queue families
    QueueFamilyIndices indices = p_device->findQueueFamilies(p_device->getPhysicalDevice());
    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    // Specifies what transform to apply to images in the swap chain
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;

    // Specifies if the alpha channel should be used for blending with other windows in the window system.
    // Most of the time this setting will not change.
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    createInfo.presentMode = presentMode;

    // Set to true to not render obscured pixel colors
    createInfo.clipped = VK_TRUE;

    // Allows for the storage of a previous swap chain if a new one needs to be created like on a window resizing.
    // This assumes that we will not need to recreate the swap chain.
    // Will address this later.
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(p_device->getLogicalDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    std::vector<VkImage> swapChainImages;

    vkGetSwapchainImagesKHR(p_device->getLogicalDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(p_device->getLogicalDevice(), swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}

void SwapChain::createImageViews() {
    // For each swapchain image, you'd create an image view
    // This involves filling out a VkImageViewCreateInfo struct and calling vkCreateImageView
    // This function should also store the image views in a std::vector
    // The image views will be destroyed in cleanupSwapChain
    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];

		// Specifies how the image data should be interpreted
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;

        // Allows you to mix the color channels around
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		// Describes what the image's purpose is and which part of the image should be accessed
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0; // No mipmapping
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(p_device->getLogicalDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create image views!");
		}
    }
}

void SwapChain::cleanupSwapChain() {
    // Here you'd destroy the swapchain and its image views
    // This involves calling vkDestroyImageView for each image view and vkDestroySwapchainKHR for the swapchain
    for (auto imageView : swapChainImageViews) 
    {
		vkDestroyImageView(p_device->getLogicalDevice(), imageView, nullptr);
	}

    vkDestroySwapchainKHR(p_device->getLogicalDevice(), swapChain, nullptr);
}
