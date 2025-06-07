#pragma once

#include "Metamorphic/Rendering/IWindow.h"

namespace Metamorphic{
    class WindowsWindow : public IWindow{
    public:
        WindowsWindow()noexcept;
        
        WindowError Create()noexcept override;
        void Destroy()noexcept override;

        void Update()noexcept override;
        void Show()noexcept override;
        void Hide()noexcept override;

        WindowError CreateOpenGLBindings()noexcept override;
    };
}