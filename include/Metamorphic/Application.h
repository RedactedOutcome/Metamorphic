#pragma once

namespace Metamorphic{
    class Application{
    public:
        Application()noexcept;
        virtual ~Application()noexcept;
    };

    extern Application* CreateApplication()noexcept;
}