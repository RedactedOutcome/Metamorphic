#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    class VulkanRenderer : public IRenderAPI{
    public:
        VulkanRenderer(IWindow* window)noexcept;
        ~VulkanRenderer()noexcept override;

        RenderAPIError Init()noexcept override;
        RenderAPIError Shutdown()noexcept override;

        void PrepareScreen() noexcept override;
        void ClearDepthBuffers()noexcept override;
        void Update()noexcept override;
    private:
        VkInstance m_Instance;
    };
}