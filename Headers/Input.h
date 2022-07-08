#ifndef REFRAENGINE_INPUT_H
#define REFRAENGINE_INPUT_H

#include <map>

#include "Render.h"
#include "Window.h"
#include "KeyCode.h"

namespace rfe {
    enum PressState {
        Unknown,
        Pressed,
        Hold,
        Released,
    };

    struct KeyData {
        int keyCode;
        int action;
    };

    struct MouseData {
        int xPos;
        int yPos;
    };

    class Input {
    private:
        MouseData mouseData;
        std::map<KeyCode, KeyData> keysData;
    public:
        void SetupCallback(Window &window);
        PressState GetKeyState(KeyCode keyCode);
        MouseData GetMouseData();
    };
}

#endif //REFRAENGINE_INPUT_H
