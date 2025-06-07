#include "Metamorphic/pch.h"
#include "Rendering/IWindow.h"

namespace Metamorphic{
    IWindow::IWindow()noexcept{}
    IWindow::~IWindow()noexcept{
        Destroy();
    }

    WindowError IWindow::Create()noexcept{
        return WindowError::None;
    }
    void IWindow::Destroy()noexcept{}

    void IWindow::Update()noexcept{}

    void IWindow::Show()noexcept{}
    void IWindow::Hide()noexcept{}

    WindowError IWindow::CreateOpenGLBindings()noexcept{
        return WindowError::None;
    }
}