//
// Created by Andrew Graser on 4/5/2025.
//

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Voxify {
    GLFWwindow* Input::mWindow = nullptr;


    void Input::Init() {
        mWindow = Application::Get().GetWindow().GetNativeWindow();
    }

    bool Input::GetKey(int keycode) {
        return glfwGetKey(mWindow, keycode);
    }
} // Voxify