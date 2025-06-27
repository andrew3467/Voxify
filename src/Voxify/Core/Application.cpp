//
// Created by Andrew Graser on 3/15/2025.
//

#include "../Voxify.h"

#include <GLFW/glfw3.h>
#include "Application.h"


namespace Voxify {
    Application* Application::sApplication = nullptr;

    EventManager EventSystem::sEventManager;

    Application *Application::CreateApplication() {
        if(!sApplication) sApplication = new Application;


        return sApplication;
    }

    Application::Application()
        : mWindowResizeHandler([this](const WindowResizeEvent& e) { OnWindowResizeEvent(e);})
    {
        Init();
    }

    Application::~Application() {
        EventSystem::Unsubscribe<WindowResizeEvent>(mWindowResizeHandler);
    }

    void Application::Init() {
        Log::Init();

        mWindow = std::make_shared<Window>();

        Input::Init();


        EventSystem::Subscribe<WindowResizeEvent>(mWindowResizeHandler);

        mRunning = true;
        VOXIFY_INFO("Engine Initialized");
    }

    void Application::Run() {


        while(mRunning) {
            //if(Input::GetKey(GLFW_KEY_W)) VOXIFY_INFO("W Down");


            EventSystem::DispatchEvents();
            mWindow->Update();
        }

        VOXIFY_INFO("Exiting Application");
    }

    void Application::Close() {
        mRunning = false;
    }

    void Application::OnWindowResizeEvent(const WindowResizeEvent &e) {
        VOXIFY_INFO("Width: {0}, Height: {1}", e.Width, e.Height);
    }
}