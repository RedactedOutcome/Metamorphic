#pragma once

#include "Morphic/pch.h"
#include "Morphic/Core.h"

namespace Morphic{
    enum class WindowAPI{
        None=0,
        Win32,
    };

    struct WindowProps{
        int32_t m_X;
        int32_t m_Y;
        int32_t m_Width;
        int32_t m_Height;
        std::string m_Title;
    };

    class MORPHIC_API Window{
    public:
        /// @brief Creates a window if allowed too.
        /// @return a pointer to newly allocated window. else nullptr if not able to
        static Window* CreateWindow() MORPHIC_NOEXCEPT;

        Window(WindowAPI api) MORPHIC_NOEXCEPT;
        virtual ~Window();

        virtual void Create();
        virtual void Destroy();
    protected:
        WindowAPI m_API = WindowAPI::None;
    };
}