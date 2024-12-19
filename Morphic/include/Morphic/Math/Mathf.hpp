#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    class Mathf{
    public:
        static constexpr double PI = 3.1415926535897932384626433832795;

        template<class T=float>
        static inline constexpr T ToRadians(T deg) MORPHIC_NOEXCEPT{return deg * static_cast<T>(PI / static_cast<T>(T));}
        template<class T=float>
        static inline constexpr T ToDegrees(T rad) MORPHIC_NOEXCEPT{return rad * static_cast<T>(static_cast<T>(180) / static_cast(PI));}

    };
}