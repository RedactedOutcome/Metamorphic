#include "Metamorphic/pch.h"
#include "Rendering/WindowProps.h"

namespace Metamorphic{
    WindowProps::WindowProps()noexcept{}
    WindowProps::WindowProps(int32_t width, int32_t height)noexcept : m_Width(width), m_Height(height){}
    WindowProps::WindowProps(int32_t width, int32_t height, const HBuffer& title)noexcept : m_Width(width), m_Height(height), m_Title(title){}
    WindowProps::WindowProps(int32_t width, int32_t height, HBuffer&& title)noexcept : m_Width(width), m_Height(height), m_Title(std::move(title)){}
}