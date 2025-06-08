#pragma once

#include "Metamorphic/pch.h"

#define METAMORPHIC_WINDOW_FULLSCREEN -1
namespace Metamorphic{
    class WindowProps{
    public:
        WindowProps()noexcept;
        WindowProps(int32_t width, int32_t height)noexcept;
        WindowProps(int32_t width, int32_t height, const HBuffer& title)noexcept;
        WindowProps(int32_t width, int32_t height, HBuffer&& title)noexcept;

        void SetX(int32_t x) noexcept{m_X = x;}
        void SetY(int32_t y) noexcept{m_Y = y;}
        void SetWidth(int32_t width) noexcept{m_Width = width;}
        void SetHeight(int32_t height) noexcept{m_Height = height;}
        void SetTitle(const HBuffer& value)noexcept{m_Title = value;}
        void SetTitle(HBuffer&& value)noexcept{m_Title = std::move(value);}
    public:
        int32_t GetX() const noexcept{return m_X;}
        int32_t GetY() const noexcept{return m_Y;}
        int32_t GetWidth() const noexcept{return m_Width;}
        int32_t GetHeight() const noexcept{return m_Height;}
        HBuffer GetTitle() const noexcept{return m_Title;}
    private:
        int32_t m_X = 0;
        int32_t m_Y = 0;
        int32_t m_Width=METAMORPHIC_WINDOW_FULLSCREEN;
        int32_t m_Height=METAMORPHIC_WINDOW_FULLSCREEN;
        HBuffer m_Title;
    };
}