#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::s_ApplicationLogger;

void Logger::Init(){
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("Core");
    s_CoreLogger->set_level(spdlog::level::trace);
    
	s_ApplicationLogger = spdlog::stdout_color_mt("Application");
    s_ApplicationLogger->set_level(spdlog::level::trace);
}