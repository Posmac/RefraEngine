#include "Input.h"

void rfe::Input::SetupCallback(rfe::Window &window) {
    glfwSetWindowUserPointer(window.GetWindow(), &keyData);
    glfwSetKeyCallback(window.GetWindow(),
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           KeyData &data = *static_cast<KeyData *>(glfwGetWindowUserPointer(window));
                           data.action = action;
                           data.keyCode = key;
                       });
}

bool rfe::Input::KeyDown(rfe::KeyCode keyCode) {
    auto code = static_cast<KeyCode>(keyData.keyCode);
    if(keyCode != code){
        return false;
    }
    if(keyData.action == GLFW_PRESS)
    {
        return true;
    }
    return false;
}

bool rfe::Input::KeyUp(rfe::KeyCode keyCode) {
    auto code = static_cast<KeyCode>(keyData.keyCode);
    if(keyCode != code){
        return false;
    }
    if(keyData.action == GLFW_RELEASE)
    {
        keyData.keyCode = -1;
        keyData.action = -1;
        return true;
    }
    return false;
}

bool rfe::Input::Key(rfe::KeyCode keyCode) {
    auto code = static_cast<KeyCode>(keyData.keyCode);
    if(keyCode != code){
        return false;
    }
    if(keyData.action == GLFW_REPEAT)
    {
        return true;
    }
    return false;
}

rfe::PressState rfe::Input::GetKeyState(rfe::KeyCode keyCode) {
    auto code = static_cast<KeyCode>(keyData.keyCode);
    if(keyCode != code){
        return rfe::Unknown;
    }
    switch (keyData.action) {
        case GLFW_PRESS:
            if(keyData.pressState == rfe::Pressed)
            {
                keyData.keyCode = -1;
                keyData.action = -1;
                break;
            }
            keyData.pressState = rfe::Pressed;
            break;
        case GLFW_RELEASE:
            if(keyData.pressState == rfe::Released)
            {
                keyData.keyCode = -1;
                keyData.action = -1;
                break;
            }
            keyData.pressState = rfe::Released;
            break;
        case GLFW_REPEAT:
            keyData.pressState = rfe::Hold;
            break;
    }
    return keyData.pressState;
}
