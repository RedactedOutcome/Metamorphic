#pragma once

#include "Metamorphic/Rendering/IWindow.h"

namespace Metamorphic{
    class METAMORPHIC_API WindowsWindow : public IWindow{
    public:
        WindowsWindow()noexcept;
        WindowsWindow(const WindowProps& props)noexcept;
        WindowsWindow(WindowProps&& props)noexcept;
        
        WindowError Create()noexcept override;
        void Destroy()noexcept override;

        void Update()noexcept override;
        void Show()noexcept override;
        void Hide()noexcept override;

        WindowError CreateOpenGLBindings()noexcept override;
    public:
        PWNDCLASSW GetClass() const noexcept{return (PWNDCLASSW)&m_Class;}
        const wchar_t* GetClassName() const noexcept{return m_ClassName;}
        bool CreatedClass() const noexcept{return m_CreatedClass;}

        HWND GetWindow() const noexcept{return m_Window;}
        HINSTANCE GetInstance() const noexcept{return m_HInstance;}
        HDC GetHDC() const noexcept{return m_HDC;}
    private:
        WNDCLASS m_Class;
        const wchar_t* m_ClassName = nullptr;
        bool m_CreatedClass = false;

        HWND m_Window;
        HINSTANCE m_HInstance;
        HDC m_HDC;
        MSG m_MSG = {};
        HGLRC m_Context;
    };
}