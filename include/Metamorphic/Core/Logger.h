#pragma once

#include "Metamorphic/pch.h"

class Logger{
public:
    static void Init();
public:
    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetSandboxLogger() { return s_SandboxLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_SandboxLogger;
};

#ifndef CONTAINMENT_PROTOCOL_DIST
    #define MORPHIC_ERROR(...)	::Logger::GetCoreLogger()->error(__VA_ARGS__)
    #define MORPHIC_WARN(...)	::Logger::GetCoreLogger()->warn(__VA_ARGS__)
    #define MORPHIC_INFO(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
    #define MORPHIC_LOG(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
    #define MORPHIC_DEBUG(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
    
    #define SANDBOX_ERROR(...)	::Logger::GetSandboxLogger()->error(__VA_ARGS__)
    #define SANDBOX_WARN(...)	::Logger::GetSandboxLogger()->warn(__VA_ARGS__)
    #define SANDBOX_INFO(...)	::Logger::GetSandboxLogger()->info(__VA_ARGS__)
    #define SANDBOX_LOG(...)	::Logger::GetSandboxLogger()->info(__VA_ARGS__)
    #define SANDBOX_DEBUG(...)	::Logger::GetSandboxLogger()->info(__VA_ARGS__)
#else
    #define MORPHIC_ERROR(...)
    #define MORPHIC_WARN(...)
    #define MORPHIC_INFO(...)
    #define MORPHIC_LOG(...)
    #define MORPHIC_DEBUG(...)
    
    #define SANDBOX_ERROR(...)
    #define SANDBOX_WARN(...)
    #define SANDBOX_INFO(...)
    #define SANDBOX_LOG(...)
    #define SANDBOX_DEBUG(...)
#endif