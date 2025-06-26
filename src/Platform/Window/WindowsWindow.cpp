#include "Metamorphic/pch.h"
#include "Platform/Window/WindowsWindow.h"
#include "Core/Logger.h"

#include "Core/Event/Events/ApplicationExitEvent.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    Metamorphic::WindowsWindow* window = reinterpret_cast<Metamorphic::WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if(!window){
        if(uMsg == WM_CREATE){
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams));
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    using namespace Metamorphic;
    switch (uMsg){
        case WM_CLOSE:{
            ApplicationExitEvent event;
            EventDispatcher* eventDispatcher = window->GetEventDispatcher();
            if(eventDispatcher)eventDispatcher->Dispatch<ApplicationExitEvent>(event);
            window->Destroy();
            PostQuitMessage(0);
            return 0;
        }
        case WM_SIZE:{
            int width = LOWORD(lParam);  // Macro to get the low-order word.
            int height = HIWORD(lParam); // Macro to get the high-order word.

            // Respond to the message:
            //OnSize(hwnd, (UINT)wParam, width, height);
            //WindowResizedEvent event(width, height);
            //Game::GetEventDispatcher().Dispatch<WindowResizedEvent>(event);
            return 0;
        }
        case WM_MOVE:{
            int x = LOWORD(lParam);  // Macro to get the low-order word.
            int y = HIWORD(lParam); // Macro to get the high-order word.
            //WindowMovedEvent event(x, y);
            //Game::GetEventDispatcher().Dispatch<WindowMovedEvent>(event);
            return 0;
        }
        case WM_MOUSEMOVE:{
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            //MouseMovedEvent event(mouseX, mouseY);
            //Game::GetEventDispatcher().Dispatch<MouseMovedEvent>(event);
            return 0;
        }
        case WM_LBUTTONDOWN:{
            
            return 0;
        }
        default:{
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
}

// Set pixel format for OpenGL
bool SetPixelFormatForGL(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
        1,                              // Version
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
        PFD_TYPE_RGBA,                 // Color type
        32,                            // Color depth
        0, 0, 0, 0, 0, 0,              // Ignored color bits
        0, 0,                          // No alpha
        0, 0, 0, 0, 0,                 // No accumulation buffer
        24,                            // Depth buffer
        8,                             // Stencil buffer
        0,                             // Aux buffers
        PFD_MAIN_PLANE,                // Layer type
        0, 0, 0, 0                     // Reserved
    };

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    if (pixelFormat == 0) return false;

    return SetPixelFormat(hdc, pixelFormat, &pfd);
}
namespace Metamorphic{
    WindowsWindow::WindowsWindow()noexcept : IWindow(){}
    WindowsWindow::WindowsWindow(const WindowProps& props)noexcept : IWindow(props){}
    WindowsWindow::WindowsWindow(WindowProps&& props)noexcept : IWindow(props){}

    WindowError WindowsWindow::Create()noexcept{
        if(m_IsCreated) return WindowError::AlreadyCreated;
        m_HInstance = GetModuleHandle(nullptr);

        if(m_ClassName == nullptr){
            HBuffer title = m_Props.GetTitle();
            const char* asciiStr = title.GetData();
            int wideLen = MultiByteToWideChar(CP_ACP, 0, asciiStr, -1, nullptr, 0);
            if (wideLen == 0) {
                return WindowError::FailedToCreateWideString;
            }

            m_ClassName = new wchar_t[wideLen];
            if (MultiByteToWideChar(CP_ACP, 0, asciiStr, -1, (LPWSTR)m_ClassName, wideLen) == 0) {
                delete[] m_ClassName;
                m_ClassName = nullptr;
                return WindowError::FailedToCreateWideString;
            }
        }
        if(!m_CreatedClass){
            memset(&m_Class, 0, sizeof(WNDCLASS));
            m_Class.lpfnWndProc   = WindowProc;
            m_Class.hInstance     = m_HInstance;
            m_Class.lpszClassName = m_ClassName;
            RegisterClass(&m_Class);
            m_CreatedClass = true;
        }
        RECT desktopRect;
        GetWindowRect(GetDesktopWindow(), &desktopRect);
        int32_t screenWidth = desktopRect.right - desktopRect.left;
        int32_t screenHeight = desktopRect.bottom - desktopRect.top;

        int32_t width = m_Props.GetWidth();
        int32_t height = m_Props.GetHeight();
        if(width = METAMORPHIC_WINDOW_FULLSCREEN){
            width = screenWidth;
            m_Props.SetWidth(width);
        }
        if(height = METAMORPHIC_WINDOW_FULLSCREEN){
            height = screenHeight;
            m_Props.SetHeight(height);
        }

        m_Props.SetX((screenWidth - width) / 2);
        m_Props.SetY((screenHeight - height) / 2);
        m_Window = CreateWindowEx(
            0,                              // Optional window styles.
            m_ClassName,                     // Window class
            m_ClassName,    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            m_Props.GetX(), m_Props.GetY(),
            width, height,

            NULL,       // Parent window    
            NULL,       // Menu
            m_HInstance,  // Instance handle
            this
        );
        if (m_Window == NULL){
            Destroy();
            return WindowError::InvalidHandle;
        }
        /// TODO: Create dummy window and set a minimum opengl context
        
        // Get device context
        m_HDC = GetDC(m_Window);
        if (!SetPixelFormatForGL(m_HDC)) {
            MessageBoxA(nullptr, "Failed to set pixel format", "Error", MB_OK);
            return WindowError::FailedToSetPixelFormat;
        }
        CreateOpenGLBindings();
        m_IsCreated = true;
        return WindowError::None;
    }

    void WindowsWindow::Destroy()noexcept{
        if(m_CreatedClass){
            UnregisterClassW(m_ClassName, m_HInstance);
            m_CreatedClass = false;
        }
        if(!m_IsCreated)return;

        // 1. Unset the current OpenGL context
        wglMakeCurrent(NULL, NULL);

        // 2. Delete the OpenGL context
        if (m_Context) {
            wglDeleteContext(m_Context);
            m_Context = nullptr;
        }

        // 3. Release the device context
        if (m_HDC && m_Window) {
            ReleaseDC(m_Window, m_HDC);
            m_HDC = nullptr;
        }

        // 4. Destroy the window
        if (m_Window) {
            DestroyWindow(m_Window);
            m_Window = nullptr;
        }
        if(m_ClassName){
            delete m_ClassName;
        }
        m_IsShowing = false;
        m_IsCreated = false;
    }

    void WindowsWindow::Update()noexcept{
        while(PeekMessage(&m_MSG, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&m_MSG);
            DispatchMessage(&m_MSG);
        }
        SwapBuffers(m_HDC);
    }
    void WindowsWindow::Show()noexcept{
        if(!m_IsCreated)return;
        ShowWindow(m_Window, SW_SHOW);
        m_IsShowing = true;
    }
    void WindowsWindow::Hide()noexcept{
        if(!m_IsCreated)return;
        ShowWindow(m_Window, SW_HIDE);
        m_IsShowing = false;
    }

    WindowError WindowsWindow::CreateOpenGLBindings()noexcept{
        m_Context = wglCreateContext(m_HDC);
        wglMakeCurrent(m_HDC, m_Context);
        return WindowError::None;
    }
}