#ifndef DEVICE_H
#define DEVICE_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); };
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = { 
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif // NDEBUG

class Device
{
public:
	Device();
	~Device();

	void setSurface(VkSurfaceKHR* surface) { p_surface = surface; };
	void setWindow(GLFWwindow* window) { p_window = window; };

	void createPhysicalAndLogicalDevices(VkInstance& instance);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	VkPhysicalDevice getPhysicalDevice() { return m_physicalDevice; };
	VkDevice getLogicalDevice() { return m_logicalDevice; };

private:
	QueueFamilyIndices m_indices;
	VkPhysicalDevice m_physicalDevice;
	VkDevice m_logicalDevice;
	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;
	VkSurfaceKHR* p_surface;
	GLFWwindow* p_window;

	void pickPhysicalDevice(VkInstance& instance);
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice();
	bool checkDeviceExtensionsSupport(VkPhysicalDevice device);
};

#endif // !DEVICE_H
