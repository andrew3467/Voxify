//
// Created by Andrew Graser on 3/15/2025.
//


#pragma once

#include <Event/ApplicationEvent.h>
#include "Window.h"


namespace Voxify {


    class Application {
    public:
        static Application* sApplication;

        static Application* CreateApplication();
        static Application& Get() {return *sApplication;}

    public:
        Application();
        ~Application();

        Window& GetWindow() {return *mWindow;}

        void Run();
        void Close();

    private:
        void OnWindowResizeEvent(const WindowResizeEvent &e);
        EventHandler<WindowResizeEvent> mWindowResizeHandler;

        void Init();

    private:
        bool mRunning = false;

        std::shared_ptr<Window> mWindow;
    };
}
