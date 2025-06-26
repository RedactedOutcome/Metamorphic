#include "Metamorphic/pch.h"
#include "Platform/Renderers/VulkanRenderer.h"
#include "Core/Core.h"

namespace Metamorphic{
    VulkanRenderer::VulkanRenderer(IWindow* window)noexcept : IRenderAPI(window){}
    VulkanRenderer::~VulkanRenderer()noexcept{}

    RenderAPIError VulkanRenderer::Init()noexcept{
        VkApplicationInfo info{};
        info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        info.pApplicationName = "Metamorphic-Project";
        info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        info.pEngineName = "Metamorphic";
        info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &info;
        createInfo.enabledLayerCount = 0;

        if(vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS){
            return RenderAPIError::FailedToCreateVulkanInstance;
        }
        return RenderAPIError::None;
    }
    RenderAPIError VulkanRenderer::Shutdown()noexcept{

        return RenderAPIError::None;
    }

    void VulkanRenderer::PrepareScreen() noexcept{

    }
    void VulkanRenderer::ClearDepthBuffers()noexcept{

    }

    void VulkanRenderer::Update()noexcept{}
}