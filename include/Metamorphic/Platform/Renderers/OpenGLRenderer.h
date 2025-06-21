#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    class OpenGLRenderer : public IRenderAPI{
    public:
        OpenGLRenderer(IWindow* window)noexcept;
        ~OpenGLRenderer()noexcept override;

        RenderAPIError Init()noexcept override;
        RenderAPIError Shutdown()noexcept override;

        void PrepareScreen() noexcept override;
        void ClearDepthBuffers()noexcept override;
    };
}