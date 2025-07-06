#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    class METAMORPHIC_API MetalRenderer : public IRenderAPI{
    public:
        MetalRenderer(IWindow* window)noexcept;
        ~MetalRenderer()noexcept override;

        RenderAPIError Init()noexcept override;
        RenderAPIError Shutdown()noexcept override;

        void PrepareScreen() noexcept override;
        void ClearDepthBuffers()noexcept override;
        void Update()noexcept override;
        
        std::unique_ptr<Shader> CreateShader()noexcept override;
    };
}