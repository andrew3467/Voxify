//
// Created by Andrew Graser on 3/15/2025.
//


#pragma once

#include "../Voxify.h"
#include <Event/ApplicationEvent.h>
#include <Event/InputEvent.h>
#include <Event/Event.h>

namespace Voxify {
    class Application {
    public:
        static Application* sApplication;

        static Application* CreateApplication();
        static Application& Get() {return *sApplication;}

    public:
        Application();
        ~Application();

        void Run();
        void Close();

    private:
        void OnWindowResizeEvent(const WindowResizeEvent &e);
        EventHandler<WindowResizeEvent> mWindowResizeHandler;

        void OnKeyPressEvent(const KeyPressEvent &e);
        EventHandler<KeyPressEvent> mKeyPressHandler;

        void OnKeyReleaseEvent(const KeyReleaseEvent &e);
        EventHandler<KeyReleaseEvent> mKeyReleaseHandler;

        void Init();

    private:
        bool mRunning = false;


    };
}
