#include "Metamorphic/pch.h"
#include "Platform/Window/WindowsWindow.h"

namespace Metamorphic{
    WindowsWindow::WindowsWindow()noexcept : IWindow(){}
    
    WindowError WindowsWindow::Create()noexcept{
        m_IsCreated = true;
        return WindowError::None;
    }

    void WindowsWindow::Destroy()noexcept{

    }

    void WindowsWindow::Update()noexcept{}
    void WindowsWindow::Show()noexcept{}
    void WindowsWindow::Hide()noexcept{}

    WindowError WindowsWindow::CreateOpenGLBindings()noexcept{
        return WindowError::None;
    }
}