#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    template<typename T>
    class Vector4{
    public:
        Vector4(){}
        Vector4(T val): m_X(val), m_Y(val), m_Z(val){}
        Vector4(T x, T y, T z) : m_X(x), m_Y(y), m_Z(z){}
        Vector4(T x, T y, T z, T w) : m_X(x), m_Y(y), m_Z(z), m_W(w){}

        Set(T val) MORPHIC_NOEXCEPT{
            m_X = val;
            m_Y = val;
            m_Z = val;
            m_W = val;
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
        Set(T x, T y, T z, T w) MORPHIC_NOEXCEPT{
            m_X = x;
            m_Y = y;
            m_Z = z;
            m_W = w;
        }
        
    public:
        T m_X = static_cast<T>(0);
        T m_Y = static_cast<T>(0);
        T m_Z = static_cast<T>(0);
        T m_W = static_cast<T>(0);
    };
}