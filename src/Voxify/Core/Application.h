//
// Created by Andrew Graser on 3/15/2025.
//


#pragma once

namespace Voxify {
    class Application {
    public:
        static Application* CreateApplication();

    public:
        Application();
        ~Application();

        void Run();

    private:
        void Init();

    private:
        bool mRunning = false;
    };
}
