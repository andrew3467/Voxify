//
// Created by Andrew Graser on 3/15/2025.
//

#include "../Voxify.h"

int main() {
    auto* app = Voxify::Application::CreateApplication();

    app->Run();

    delete app;

    return 1;
}
