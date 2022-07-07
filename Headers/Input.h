#ifndef REFRAENGINE_INPUT_H
#define REFRAENGINE_INPUT_H

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
        PressState pressState;
    };

    class Input {
    private:
        KeyData keyData;
    public:
        void SetupCallback(Window &window);
        PressState GetKeyState(KeyCode keyCode);
    private:
    };
}

#endif //REFRAENGINE_INPUT_H
