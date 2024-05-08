#include "Zed/Core/Log.h"

namespace Zed{

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n : %v%$");
        Log::s_CoreLogger = spdlog::stdout_color_mt("ZED", spdlog::color_mode::always);
        Log::s_CoreLogger->set_level(spdlog::level::trace);
        Log::s_ClientLogger = spdlog::stdout_color_mt("APP", spdlog::color_mode::always);
        Log::s_ClientLogger->set_level(spdlog::level::trace);
    }
}