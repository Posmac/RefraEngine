#include "Input.h"

void rfe::Input::SetupCallback(rfe::Window &window) {
    glfwSetWindowUserPointer(window.GetWindow(), &keysData);
    glfwSetKeyCallback(window.GetWindow(),
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           std::map<KeyCode, KeyData> &mapData =
                                   *static_cast<std::map<KeyCode, KeyData> *>(glfwGetWindowUserPointer(window));
                           KeyData data{};
                           data.action = action;
                           data.keyCode = key;
                           mapData[static_cast<KeyCode>(key)] = data;
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
