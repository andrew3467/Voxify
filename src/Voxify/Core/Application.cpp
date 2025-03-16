//
// Created by Andrew Graser on 3/15/2025.
//

#include "Application.h"


namespace Voxify {

    Application *Application::CreateApplication() {
        return new Application;
    }

    Application::Application() {
        Init();
    }

    Application::~Application() {

    }

    void Application::Init() {
        Log::Init();



        mRunning = true;
        VOXIFY_INFO("Engine Initialized");
    }

    void Application::Run() {

        while(mRunning) {

        }

        VOXIFY_INFO("Exiting Application");
    }
}