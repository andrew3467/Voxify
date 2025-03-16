//
// Created by Andrew Graser on 2/14/2025.
//

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>


namespace Voxify {
    std::shared_ptr<spdlog::logger> Log::sClientLogger = nullptr;
    std::shared_ptr<spdlog::logger> Log::sCoreLogger = nullptr;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        sClientLogger = spdlog::stdout_color_mt("Client");
        sClientLogger->set_level(spdlog::level::trace);

        sCoreLogger = spdlog::stdout_color_mt("Tungsten");
        sCoreLogger->set_level(spdlog::level::trace);
    }
} // Voxify