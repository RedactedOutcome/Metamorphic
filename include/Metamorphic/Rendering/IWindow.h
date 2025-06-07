#pragma once

#include "Metamorphic/pch.h"

namespace Metamorphic{
    enum class WindowError : uint8_t{
        None=0
    };
    class IWindow{
    public:
        IWindow()noexcept;
        virtual ~IWindow()noexcept=0;

        virtual WindowError Create()noexcept=0;
        virtual void Destroy()noexcept=0;

        virtual void Update()noexcept=0;

        virtual void Show()noexcept=0;
        virtual void Hide()noexcept=0;

        virtual WindowError CreateOpenGLBindings()noexcept=0;
    public:
        bool IsCreated() const noexcept{return m_IsCreated;}
        bool IsShowing() const noexcept{return m_IsShowing;}
    protected:
        bool m_IsCreated = false;
        bool m_IsShowing = false;
    };
}