#include "Window.h"

rfe::Window::Window(int screenWidth, int screenHeight, const std::string windowName)
    : ScreenHeight(screenHeight), ScreenWidth(screenWidth)
{
    window = glfwCreateWindow(ScreenWidth, ScreenHeight,
                     windowName.data(), NULL, NULL);
    if (!window)
    {
        std::cout << "Window creation failed" << '\n';
        glfwTerminate();
        CreationSuccess = false;
        return;
    }
    CreationSuccess = true;
    glfwSetKeyCallback(window, &ProcessInput);
}

void rfe::Window::SetWindowHint(unsigned int hintEnum, int value)
{
    glfwWindowHint(hintEnum, value);
}

void rfe::Window::SetContextCurrent()
{
    glfwMakeContextCurrent(window);
}

void rfe::Window::ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

bool rfe::Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void rfe::Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void rfe::Window::Destroy()
{
    glfwDestroyWindow(window);
}

GLFWwindow* rfe::Window::GetWindow()
{
    return window;
}
