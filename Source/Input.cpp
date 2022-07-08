#include "Input.h"

void rfe::Input::SetupCallback(rfe::Window &window) {
    glfwSetWindowUserPointer(window.GetWindow(), this);
    glfwSetKeyCallback(window.GetWindow(),
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           Input &input =
                                   *static_cast<Input*>(glfwGetWindowUserPointer(window));
                           KeyData data{};
                           data.action = action;
                           data.keyCode = key;
                           input.keysData[static_cast<KeyCode>(key)] = data;
                       });

    glfwSetCursorPosCallback(window.GetWindow(),
                             [](GLFWwindow* window, double xpos, double ypos)
                             {
                                 Input &input =
                                         *static_cast<Input*>(glfwGetWindowUserPointer(window));
                                input.mouseData.xPos = xpos;
                                input.mouseData.yPos = ypos;
                             });
}

rfe::PressState rfe::Input::GetKeyState(rfe::KeyCode keyCode) {

    if(keysData.count(keyCode) == 0){
        return rfe::Unknown;
    }

    rfe::KeyData keyData = keysData[keyCode];
    auto keyCodeData = static_cast<KeyCode>(keyData.keyCode);

    if(keyCode != keyCodeData){
        return rfe::Unknown;
    }

    switch (keyData.action) {
        case GLFW_PRESS:
        case GLFW_REPEAT:
            return rfe::Pressed;
        case GLFW_RELEASE:
            return rfe::Released;
    }

    return rfe::Unknown;
}

rfe::MouseData rfe::Input::GetMouseData() {
    return mouseData;
}
