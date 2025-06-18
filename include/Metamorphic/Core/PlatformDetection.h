#pragma once

/// @brief Included in the pch.h

/// @brief Check Platform
#if defined(_WIN32)
    #define METAMORPHIC_PLATFORM_WINDOWS
#elif defined(__ANDROID__)
    #define METAMORPHIC_PLATFORM_ANDROID
#elif defined(__linux__)
    #define METAMORPHIC_PLATFORM_LINUX
#else
    #error "Metamorphic was unable to detect platform!"
#endif