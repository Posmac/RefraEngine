#include "Window.h"

rfe::Window::Window(int screenWidth, int screenHeight, const std::string windowName)
        : ScreenHeight(screenHeight), ScreenWidth(screenWidth) {
    window = glfwCreateWindow(ScreenWidth, ScreenHeight,
                              windowName.data(), NULL, NULL);
    if (!window) {
        std::cout << "Window creation failed" << '\n';
        glfwTerminate();
        CreationSuccess = false;
        return;
    }
    CreationSuccess = true;
}

void rfe::Window::SetWindowHint(unsigned int hintEnum, int value) {
    glfwWindowHint(hintEnum, value);
}

void rfe::Window::SetContextCurrent() {
    glfwMakeContextCurrent(window);
}

bool rfe::Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

void rfe::Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

void rfe::Window::Destroy() {
    glfwDestroyWindow(window);
}

GLFWwindow *rfe::Window::GetWindow() {
    return window;
}

void rfe::Window::SetWindowClose() {
    glfwSetWindowShouldClose(window, true);
}
