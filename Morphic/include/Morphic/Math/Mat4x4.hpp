#pragma once

#include "Morphic/pch.h"

namespace Morphic{
    class Mat4x4{
    public:
        void SetIdentity(){
            for(uint8_t i = 1; i < 15; i++)m_Data[i] = 0;
            m_Data[0] = 1;
            m_Data[5] = 1;
            m_Data[10] = 1;
            m_Data[15] = 1;
        }
        
    public:
        float m_Data[16];
    };
}