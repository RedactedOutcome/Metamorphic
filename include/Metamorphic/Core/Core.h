#pragma once

/// Default to 3D Game
#ifndef METAMORPHIC_2D_GAME
    #ifndef METAMORPHIC_3D_GAME
        #error "Metamorphic no game type specified. Either specify 3D or 2D in the cmake"
    #endif
#endif

#if defined(METAMORPHIC_2D_GAME) && defined(METAMORPHIC_3D_GAME)
    #error "Metamorphic 2D and 3D game specified. May only be one or the other"
#endif

#ifdef METAMORPHIC_3D_GAME
    #define METAMORPHIC_DEFAULT_VECTOR_TYPE sfmath::Vec3
#else
    #define METAMORPHIC_DEFAULT_VECTOR_TYPE sfmath::Vec2
#endif

#ifdef METAMORPHIC_STATIC
    #define METAMORPHIC_API 
#else
    #ifdef METAMORPHIC_EXPORTS
        #define METAMORPHIC_API __declspec(dllexport)
    #else
        #define METAMORPHIC_API __declspec(dllimport)
    #endif
#endif