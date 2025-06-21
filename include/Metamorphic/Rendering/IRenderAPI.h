#pragma once

#include "IWindow.h"

namespace Metamorphic{
    enum class RenderAPIError{
        None=0
    };
    class IRenderAPI{
    public:
        IRenderAPI(IWindow* window)noexcept;
        virtual ~IRenderAPI()noexcept;

        virtual RenderAPIError Init()noexcept=0;
        virtual RenderAPIError Shutdown()noexcept=0;
        virtual void PrepareScreen()noexcept=0;
        virtual void ClearDepthBuffers()noexcept=0;
    protected:
        IWindow* m_Window = nullptr;
    };
}