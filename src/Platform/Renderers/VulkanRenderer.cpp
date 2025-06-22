#include "Metamorphic/pch.h"
#include "Platform/Renderers/VulkanRenderer.h"

namespace Metamorphic{
    VulkanRenderer::VulkanRenderer(IWindow* window)noexcept : IRenderAPI(window){}
    VulkanRenderer::~VulkanRenderer()noexcept{}

    RenderAPIError VulkanRenderer::Init()noexcept{
        return RenderAPIError::None;
    }
    RenderAPIError VulkanRenderer::Shutdown()noexcept{
        
        return RenderAPIError::None;
    }

    void VulkanRenderer::PrepareScreen() noexcept{

    }
    void VulkanRenderer::ClearDepthBuffers()noexcept{

    }
}