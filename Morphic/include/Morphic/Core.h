#pragma once

// Build Configurations
//  MORPHIC_DEBUG    MORPHIC_RELEASE    MORPHIC_DIST

#define MORPHIC_ASSERT(x, ...)

#ifdef MORPHIC_EXPORTS
#define MORPHIC_API __declspec(dllexport)
#else
#define MORPHIC_API __declspec(dllimport)
#endif

#define MORPHIC_NOEXCEPT noexcept