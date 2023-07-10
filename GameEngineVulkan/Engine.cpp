#include "Engine.h"

Engine::~Engine()
{
	m_vulkan->cleanupVulkan();
}

Engine* Engine::GetInstance()
{
	if (m_engine == nullptr)
	{
		m_engine = new Engine();
	}

	return m_engine;
}

void Engine::setInfo(int width, int height, std::string title) 
{
	m_winWidth = width;
	m_winHeight = height;
	m_title = title;
}

void Engine::initEngine()
{
	m_window = new Window(m_winWidth, m_winHeight, m_title.c_str());
	m_vulkan = Vulkan::getInstance();
	m_vulkan->setTitle(m_title);
	m_vulkan->setWindow(m_window->GetGLFWwindow());
	m_vulkan->setWidth(m_winWidth);
	m_vulkan->setHeight(m_winHeight);
	m_vulkan->initVulkan();
}

void Engine::mainLoop()
{
	while (!m_window->ShouldClose()) {
		glfwPollEvents();
	}
}

Engine* Engine::m_engine = nullptr;