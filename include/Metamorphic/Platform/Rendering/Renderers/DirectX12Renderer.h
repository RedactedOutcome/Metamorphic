#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    class METAMORPHIC_API DirectX12Renderer : public IRenderAPI{
    public:
        DirectX12Renderer(IWindow* window)noexcept;
        ~DirectX12Renderer()noexcept override;

        RenderAPIError Init()noexcept override;
        RenderAPIError Shutdown()noexcept override;

        void PrepareScreen() noexcept override;
        void ClearDepthBuffers()noexcept override;
        void Update()noexcept override;

        std::unique_ptr<Shader> CreateShader()noexcept override;
    private:
        
    };
}