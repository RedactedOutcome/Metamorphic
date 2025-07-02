#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    class METAMORPHIC_API OpenGLRenderer : public IRenderAPI{
    public:
        OpenGLRenderer(IWindow* window)noexcept;
        ~OpenGLRenderer()noexcept override;

        RenderAPIError Init()noexcept override;
        RenderAPIError Shutdown()noexcept override;

        void PrepareScreen() noexcept override;
        void ClearDepthBuffers()noexcept override;
        void Update()noexcept override;
    };
}