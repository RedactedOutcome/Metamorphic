#pragma once

#include "IWindow.h"

namespace Metamorphic{
    enum class RenderAPI{
        None=0,
        OpenGL
    };
    enum class RenderAPIError{
        None=0,
        FailedToInitializeOpenGL,
        FailedToCreateVulkanInstance,
        FailedToFindGraphicsCard,
        FailedToCreatePhysicalDevice
    };
    class IRenderAPI{
    public:
        IRenderAPI(IWindow* window)noexcept;
        virtual ~IRenderAPI()noexcept;

        virtual RenderAPIError Init()noexcept=0;
        virtual RenderAPIError Shutdown()noexcept=0;
        virtual void PrepareScreen()noexcept=0;
        virtual void ClearDepthBuffers()noexcept=0;
        virtual void Update()noexcept=0;
    protected:
        IWindow* m_Window = nullptr;
        RenderAPI m_RenderAPI = RenderAPI::None;
    };
}