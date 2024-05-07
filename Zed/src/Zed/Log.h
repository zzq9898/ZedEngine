#ifndef ZED_LOG_H
#define ZED_LOG_H

#include <memory>
//#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Zed {
    class Log {
    public:

        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){
            return s_CoreLogger;
        }

        inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){
            return s_ClientLogger;
        };

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define ZED_CORE_TRACE(...)  ::Zed::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZED_CORE_INFO(...)   ::Zed::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZED_CORE_WARN(...)   ::Zed::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZED_CORE_ERROR(...)  ::Zed::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZED_CORE_FATAL(...)  ::Zed::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// Client log macros
#define ZED_TRACE(...)  ::Zed::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZED_INFO(...)   ::Zed::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZED_WARN(...)   ::Zed::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZED_ERROR(...)  ::Zed::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZED_FATAL(...)  ::Zed::Log::GetClientLogger()->fatal(__VA_ARGS__)
#endif //ZED_LOG_H