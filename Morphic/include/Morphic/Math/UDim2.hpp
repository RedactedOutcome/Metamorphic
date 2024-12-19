#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    template<class SCALE_T=float,class OFFSET_T=short>
    class UDim2{
    public:
        SCALE_T m_ScaleX = 1;
        SCALE_T m_ScaleY = 1;
        OFFSET_T m_OffsetX = 0;
        OFFSET_T m_OffsetY = 0;

        UDim2() MORPHIC_NOEXCEPT :m_ScaleX(1),m_ScaleY(1), m_OffsetX(0), m_OffsetY(0){}
        UDim2(SCALE_T scaleX, SCALE_T scaleY) MORPHIC_NOEXCEPT{
            m_ScaleX = scaleX;
            m_ScaleY = scaleY;
        }

        UDim2(SCALE_T scaleX, SCALE_T scaleY, OFFSET_T offsetX, OFFSET_T offsetY) MORPHIC_NOEXCEPT :
            m_ScaleX(scaleX), m_ScaleY(scaleY), m_OffsetX(offsetX),m_OffsetY(offsetY){}
        
        const UDim2<SCALE_T, OFFSET_T> operator+(UDim2<SCALE_T, OFFSET_T>& right)MORPHIC_NOEXCEPT{
            UDim2<SCALE_T, OFFSET_T> both = *this;
            both.m_ScaleX += right.m_ScaleX;
            both.m_ScaleY += right.m_ScaleY;
            both.m_OffsetX += right.m_OffsetX;
            both.m_OffsetY += right.m_OffsetY;
        }
        const UDim2<SCALE_T, OFFSET_T> operator+(UDim2<SCALE_T, OFFSET_T>& right)MORPHIC_NOEXCEPT{
            UDim2<SCALE_T, OFFSET_T> both = *this;
            both.m_ScaleX -= right.m_ScaleX;
            both.m_ScaleY -= right.m_ScaleY;
            both.m_OffsetX -= right.m_OffsetX;
            both.m_OffsetY -= right.m_OffsetY;
        }
        
    };
}