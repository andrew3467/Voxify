//
// Created by Andrew Graser on 3/18/2025.
//

#include "Window.h"

#include <Event/InputEvent.h>
#include "Application.h"

#include <GLFW/glfw3.h>

bool sGLFWInitialized = false;

namespace Voxify {
    Window::Window() : Window({1280, 720, "Voxify", false}) {}
    Window::Window(const Voxify::Window::WindowProps &props) {
        mData.Width = props.Width;
        mData.Height = props.Height;
        mData.Title = props.Title;
        mData.VSync = props.VSync;

        CreateWindow();
    }

    Window::~Window() {

    }

    void InitGLFW() {
        int success = glfwInit();
        VOXIFY_ASSERT(success, "ERROR: Failed to initialize GLFW!");

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        sGLFWInitialized = true;
    }

    void Window::CreateWindow() {
        if(!sGLFWInitialized) InitGLFW();

        mWindowHandle = glfwCreateWindow(mData.Width, mData.Height, mData.Title.c_str(), nullptr, nullptr);

        VOXIFY_ASSERT(mWindowHandle, "Failed to create GLFW window!");

        glfwMakeContextCurrent(mWindowHandle);
        glfwSetWindowUserPointer(mWindowHandle, &mData);

        glfwSetWindowCloseCallback(mWindowHandle, [](GLFWwindow* window) {
            Application::Get().Close();
        });

        glfwSetWindowSizeCallback(mWindowHandle, [](GLFWwindow* window, int width, int height) {
            auto data = (WindowData*) glfwGetWindowUserPointer(window);
            data->Width = width;
            data->Height = height;

            glfwSetWindowSize(window, width, height);

            EventSystem::TriggerEvent(WindowResizeEvent(width, height));
        });

        glfwSetKeyCallback(mWindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            switch (action) {
                case GLFW_PRESS: EventSystem::TriggerEvent(KeyPressEvent(key)); return;
                case GLFW_RELEASE: EventSystem::TriggerEvent(KeyReleaseEvent(key)); return;
                case GLFW_REPEAT: return; //TODO: Implemented repeat for text input
            }
        });
    }

    void Window::Update() {
        glfwSwapBuffers(mWindowHandle);
        glfwPollEvents();
    }

    void Window::ToggleCursor(bool b)
    {
        glfwSetInputMode((GLFWwindow*)mWindowHandle, GLFW_CURSOR, b ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }
}