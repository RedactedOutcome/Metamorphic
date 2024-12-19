#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    template<typename T>
    class Vector3{
    public:
        Vector3(){}
        Vector3(T val): m_X(val), m_Y(val), m_Z(val){}
        Vector3(T x, T y, T z) : m_X(x), m_Y(y), m_Z(z){}

        Set(T val) MORPHIC_NOEXCEPT{
            m_X = val;
            m_Y = val;
            m_Z = val;
        }
        Set(T x, T y) MORPHIC_NOEXCEPT{
            m_X = x;
            m_Y = y;
        }
        Set(T x, T y, T z) MORPHIC_NOEXCEPT{
            m_X = x;
            m_Y = y;
            m_Z = z;
        }

    public:
        T m_X = static_cast<T>(0);
        T m_Y = static_cast<T>(0);
        T m_Z = static_cast<T>(0);
    };
}