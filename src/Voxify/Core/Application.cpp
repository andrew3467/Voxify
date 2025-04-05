//
// Created by Andrew Graser on 3/15/2025.
//

#include <Event/InputEvent.h>
#include "Application.h"


namespace Voxify {
    Application* Application::sApplication = nullptr;

    EventManager EventSystem::sEventManager;

    Application *Application::CreateApplication() {
        if(!sApplication) sApplication = new Application;


        return sApplication;
    }

    Application::Application()
        : mWindowResizeHandler([this](const WindowResizeEvent& e) { OnWindowResizeEvent(e);}),
          mKeyPressHandler([this](const KeyPressEvent& e) { OnKeyPressEvent(e);}),
          mKeyReleaseHandler([this](const KeyReleaseEvent& e) { OnKeyReleaseEvent(e);})
    {
        Init();
    }

    Application::~Application() {
        EventSystem::Unsubscribe<WindowResizeEvent>(mWindowResizeHandler);
        EventSystem::Unsubscribe<KeyPressEvent>(mKeyPressHandler);
        EventSystem::Unsubscribe<KeyReleaseEvent>(mKeyReleaseHandler);
    }

    void Application::Init() {
        Log::Init();



        EventSystem::Subscribe<WindowResizeEvent>(mWindowResizeHandler);
        EventSystem::Subscribe<KeyPressEvent>(mKeyPressHandler);
        EventSystem::Subscribe<KeyReleaseEvent>(mKeyReleaseHandler);

        mRunning = true;
        VOXIFY_INFO("Engine Initialized");
    }

    void Application::Run() {

        Window window;

        while(mRunning) {



            EventSystem::DispatchEvents();
            window.Update();
        }

        VOXIFY_INFO("Exiting Application");
    }

    void Application::Close() {
        mRunning = false;
    }

    void Application::OnWindowResizeEvent(const WindowResizeEvent &e) {
        VOXIFY_INFO("Width: {0}, Height: {1}", e.Width, e.Height);
    }

    void Application::OnKeyPressEvent(const KeyPressEvent &e) {
        VOXIFY_INFO("Key Pressed: {0}", e.KeyCode);
    }

    void Application::OnKeyReleaseEvent(const KeyReleaseEvent &e) {
        VOXIFY_INFO("Key Released: {0}", e.KeyCode);
    }
}