#pragma once 

#include "Core/PlatformDetection.h"

/// @brief C++17 standard library
#include <iostream>
#include <fstream>

#include <functional>
#include <algorithm>

#include <chrono>
#include <string>

#include <functional>
#include <array>
#include <vector>
#include <bitset>

#include <cstdint>
#include <filesystem>
#include <map>
#include <unordered_map>
#include <type_traits>

#include <filesystem>

/// @brief Memory Management
#include <HBuffer/HBuffer.hpp>

/// @brief Spdlogger
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/// @brief Math
#include <sfmath/Quat.h>
#include <sfmath/Vec3.hpp>
#include <sfmath/Vec2.hpp>
#include <sfmath/HMat4x4.h>
#include <sfmath/SMat4x4.h>
//#include <sfmath/PMat4x4.h>

/// @brief Platform Specific Macros/Includes
#ifdef METAMORPHIC_PLATFORM_WINDOWS
    #define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10
    #define _WIN32_WINNT 0x0A00

    #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
    #define NOMINMAX             // Prevents min/max macros from being defined

    #ifndef UNICODE
    #define UNICODE
    #define UNICODE_WAS_UNDEFINED
    #endif

    #include <Windows.h>
    #undef APIENTRY  // Undefine conflicting macro

    #ifdef UNICODE_WAS_UNDEFINED
    #undef UNICODE
    #endif
#elif
#error Unsupported Metamorphic Platform
#endif