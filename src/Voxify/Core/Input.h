//
// Created by Andrew Graser on 4/5/2025.
//


#pragma once

#include "../Voxify.h"

class GLFWwindow;

namespace Voxify {
    class Input {
    public:
        static void Init();

        static bool GetKey(int keycode);


    private:
        static GLFWwindow* mWindow;
    };
}
