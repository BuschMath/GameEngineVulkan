#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    GLFWwindow* GetGLFWwindow() const;
    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;

private:
    GLFWwindow* m_window;

    static void ErrorCallback(int error, const char* description);
};

#endif // WINDOW_H
