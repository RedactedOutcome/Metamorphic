#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    struct QueueFamilyIndices {
        std::optional<uint32_t> m_GraphicsFamily;
        std::optional<uint32_t> m_PresentFamily;

        bool IsComplete()const noexcept{
            return m_GraphicsFamily.has_value() && m_PresentFamily.has_value();
        }
    };

    class METAMORPHIC_API VulkanRenderer : public IRenderAPI{
    public:
        VulkanRenderer(IWindow* window)noexcept;
        ~VulkanRenderer()noexcept override;

        RenderAPIError Init()noexcept override;
        RenderAPIError Shutdown()noexcept override;

        void PrepareScreen() noexcept override;
        void ClearDepthBuffers()noexcept override;
        void Update()noexcept override;
        
        std::unique_ptr<Shader> CreateShader()noexcept override;
    private:
        RenderAPIError CreateDevice()noexcept;
        bool IsDeviceSuitable(VkPhysicalDevice device)const noexcept;
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)const noexcept;
    private:
        VkInstance m_Instance = VK_NULL_HANDLE;
        VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice m_Device = VK_NULL_HANDLE;
        VkQueue m_PresentQueue = VK_NULL_HANDLE;
    };
}