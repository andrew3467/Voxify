//
// Created by Andrew Graser on 2/14/2025.
//


#pragma once

#include <spdlog/spdlog.h>


namespace Voxify {
    class Log {
    public:
        static void Init();

        static spdlog::logger& GetCoreLogger() {return *sCoreLogger;}
        static spdlog::logger& GetClientLogger() {return *sClientLogger;}


    private:
        static std::shared_ptr<spdlog::logger> sClientLogger;
        static std::shared_ptr<spdlog::logger> sCoreLogger;
    };
}

#define VOXIFY_TRACE(...) ::Voxify::Log::GetCoreLogger().trace(__VA_ARGS__)
#define VOXIFY_INFO(...) ::Voxify::Log::GetCoreLogger().info(__VA_ARGS__)
#define VOXIFY_WARN(...) ::Voxify::Log::GetCoreLogger().warn(__VA_ARGS__)
#define VOXIFY_ERROR(...) ::Voxify::Log::GetCoreLogger().error(__VA_ARGS__)
#define VOXIFY_FATAL(...) ::Voxify::Log::GetCoreLogger().critital(__VA_ARGS__)
#define VOXIFY_ASSERT(x, ...) { if(!(x)) { VOXIFY_ERROR(__VA_ARGS__); }}
