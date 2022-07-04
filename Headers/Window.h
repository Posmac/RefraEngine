#ifndef REFRAENGINE_WINDOW_H
#define REFRAENGINE_WINDOW_H

#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace rfe
{
    class Window
    {
    private:
        GLFWwindow *window;
    public:
        const int ScreenWidth;
        const int ScreenHeight;
        bool CreationSuccess;
    private:
        static void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    public:
        Window(int screenWidth, int screenHeight, const std::string windowName);
        void SetWindowHint(unsigned int hintEnum, int value);
        void SetContextCurrent();
        bool ShouldClose();
        void SwapBuffers();
        void Destroy();
    };
}

#endif //REFRAENGINE_WINDOW_H
