#include "Metamorphic/pch.h"
#include "Platform/Renderers/VulkanRenderer.h"

namespace Metamorphic{
    VulkanRenderer::VulkanRenderer(IWindow* window)noexcept : IRenderAPI(window){}
    VulkanRenderer::~VulkanRenderer()noexcept{}

    RenderAPIError VulkanRenderer::Init()noexcept{
        VkInstanceCreateInfo info;
        info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = VK_VALIDATION_CHECK_ALL_EXT;
        info.pApplicationInfo = nullptr;
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