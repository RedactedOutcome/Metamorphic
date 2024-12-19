#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    template<typename T>
    class Vector2{
    public:
        Vector2(){}
        Vector2(T val): m_X(val), m_Y(val){}
        Vector2(T x, T y) : m_X(x), m_Y(y){}

        Set(T val) MORPHIC_NOEXCEPT{
            m_X = val;
            m_Y = val;
        }
        Set(T x, T y) MORPHIC_NOEXCEPT{
            m_X = x;
            m_Y = y;
        }
        
    public:
        T m_X = static_cast<T>(0);
        T m_Y = static_cast<T>(0);
    };
}