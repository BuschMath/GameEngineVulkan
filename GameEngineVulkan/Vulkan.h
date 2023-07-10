#ifndef VULKAN_H
#define VULKAN_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "Device.h"
#include "SwapChain.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <optional>
#include <set>

class Vulkan
{
public:
	~Vulkan();

	static Vulkan* getInstance();
	void initVulkan();
	void setupDebugMessenger();
	void cleanupVulkan();
	void setTitle(std::string title) { m_title = title; };
	void setWindow(GLFWwindow* window) { p_window = window; };
	void setWidth(int width) { p_winWidth = width; };
	void setHeight(int height) { p_winHeight = height; };

private:
	VkInstance m_instance;
	static Vulkan* m_vulkan;
	std::string m_title;
	VkDebugUtilsMessengerEXT m_debugMessenger;
	VkSurfaceKHR m_surface;
	GLFWwindow* p_window;
	Device* m_device;
	SwapChain* m_swapChain;
	int p_winWidth;
	int p_winHeight;

	Vulkan() {
		m_device = new Device();
	};
	void createInstance();
	void createSurface();
	void createSwapChain();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageServerity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);
	VkResult CreateDebugUtilsMessengerEXT(VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator);
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
};

#endif // !VULKAN_H

