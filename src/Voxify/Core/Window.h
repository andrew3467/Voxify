//
// Created by Andrew Graser on 3/18/2025.
//


#pragma once

class GLFWwindow;

namespace Voxify {
    class Window {
    public:
        struct WindowProps {
            uint32_t Width;
            uint32_t Height;

            std::string Title;

            bool VSync = true;
        };

    public:
        Window();
        Window(const WindowProps& props);
        ~Window();

        void Update();

        GLFWwindow* GetNativeWindow() const {return mWindowHandle;}

        void ToggleCursor(bool b);

    private:
        void CreateWindow();

    private:
        GLFWwindow* mWindowHandle;

        struct WindowData {
            uint32_t Width;
            uint32_t Height;

            std::string Title;

            bool VSync = true;

        } mData;
    };
}
