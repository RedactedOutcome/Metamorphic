#pragma once

#include "Window.h"

namespace Morphic{
    class MORPHIC_API Win32Window : public Window{
    public:
        Win32Window() noexcept;
        ~Win32Window() override;

        void Create() override;
        void Destroy() override;
    };
}