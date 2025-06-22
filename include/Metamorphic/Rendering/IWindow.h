#pragma once

#include "Metamorphic/Core/Event/EventDispatcher.h"
#include "WindowProps.h"

namespace Metamorphic{
    enum class WindowError : uint8_t{
        None=0,
        AlreadyCreated,
        InvalidHandle,
        FailedToCreateWideString,
        FailedToSetPixelFormat
    };
    class IWindow{
    public:
        IWindow()noexcept;
        IWindow(const WindowProps& props)noexcept;
        IWindow(WindowProps&& props)noexcept;
        virtual ~IWindow()noexcept=0;

        virtual WindowError Create()noexcept=0;
        virtual void Destroy()noexcept=0;

        virtual void Update()noexcept=0;

        virtual void Show()noexcept=0;
        virtual void Hide()noexcept=0;

        virtual WindowError CreateOpenGLBindings()noexcept=0;
    public:
        void SetEventDispatcher(EventDispatcher* eventDispatcher) noexcept{m_EventDispatcher = eventDispatcher;}
    public:
        EventDispatcher* GetEventDispatcher() const noexcept{return m_EventDispatcher;}
        const WindowProps& GetWindowProps() const noexcept{return m_Props;}
        bool IsCreated() const noexcept{return m_IsCreated;}
        bool IsShowing() const noexcept{return m_IsShowing;}
    protected:
        EventDispatcher* m_EventDispatcher = nullptr;
        WindowProps m_Props;
        bool m_IsCreated = false;
        bool m_IsShowing = false;
    };
}