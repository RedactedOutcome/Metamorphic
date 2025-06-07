#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::s_SandboxLogger;

void Logger::Init(){
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("Core");
    s_CoreLogger->set_level(spdlog::level::trace);
    
	s_SandboxLogger = spdlog::stdout_color_mt("Sandbox");
    s_SandboxLogger->set_level(spdlog::level::trace);
}