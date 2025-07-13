#pragma once

#include "Metamorphic/pch.h"

class Logger{
public:
    static void Init();
public:
#ifdef METAMORPHIC_USE_SPDLOG
    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return s_ApplicationLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ApplicationLogger;
#endif
};

#ifndef CONTAINMENT_PROTOCOL_DIST
    #ifdef METAMORPHIC_USE_SPDLOG
        #define MORPHIC_ERROR(...)	::Logger::GetCoreLogger()->error(__VA_ARGS__)
        #define MORPHIC_WARN(...)	::Logger::GetCoreLogger()->warn(__VA_ARGS__)
        #define MORPHIC_INFO(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
        #define MORPHIC_LOG(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
        #define MORPHIC_DEBUG(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
        
        #define APPLICATION_ERROR(...)	::Logger::GetApplicationLogger()->error(__VA_ARGS__)
        #define APPLICATION_WARN(...)	::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
        #define APPLICATION_INFO(...)	::Logger::GetApplicationLogger()->info(__VA_ARGS__)
        #define APPLICATION_LOG(...)	::Logger::GetApplicationLogger()->info(__VA_ARGS__)
        #define APPLICATION_DEBUG(...)	::Logger::GetApplicationLogger()->info(__VA_ARGS__)
    #else
        #error No Logging Library Specified
    #endif
#else
    #define MORPHIC_ERROR(...)
    #define MORPHIC_WARN(...)
    #define MORPHIC_INFO(...)
    #define MORPHIC_LOG(...)
    #define MORPHIC_DEBUG(...)
    
    #define Application_ERROR(...)
    #define Application_WARN(...)
    #define Application_INFO(...)
    #define Application_LOG(...)
    #define Application_DEBUG(...)
#endif