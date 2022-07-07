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

    class Input {
    private:
        std::map<KeyCode, KeyData> keysData;
    public:
        void SetupCallback(Window &window);
        PressState GetKeyState(KeyCode keyCode);
    };
}

#endif //REFRAENGINE_INPUT_H
