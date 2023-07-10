#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Vulkan.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Subject.h"

class Engine
{
public:
	~Engine();

	static Engine* GetInstance();
	void setInfo(int width, int height, std::string title);
	void initEngine();
	void mainLoop();

	int getWidth() { return m_winWidth; };
	int getHeight() { return m_winHeight; };
	std::string getTitle() { return m_title; };

private:
	int m_winWidth;
	int m_winHeight;
	std::string m_title;
	static Engine* m_engine;
	Vulkan* m_vulkan;
	Window* m_window;

	Engine() {};
};

#endif // !ENGINE_H

