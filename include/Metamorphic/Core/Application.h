#pragma once

#include "Metamorphic/Rendering/IWindow.h"

namespace Metamorphic{
    class Application{
    public:
        Application()noexcept;
        virtual ~Application()noexcept;

        void Run()noexcept;
    protected:
        std::unique_ptr<IWindow> m_Window;
    };

    extern Application* CreateApplication()noexcept;
}