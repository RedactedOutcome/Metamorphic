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

        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &info;
        instanceCreateInfo.enabledLayerCount = 0;

        if(vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS){
            return RenderAPIError::FailedToCreateVulkanInstance;
        }
        /// Pick Physical Device
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

        if(deviceCount == 0){
            return RenderAPIError::FailedToFindGraphicsCard;
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

        m_PhysicalDevice = VK_NULL_HANDLE;
        for (const auto& device : devices) {
            if (IsDeviceSuitable(device)) {
                m_PhysicalDevice = device;
                break;
            }
        }
        /// Create Logical Device
        QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.m_GraphicsFamily.value();
        queueCreateInfo.queueCount = 1;

        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;

    #ifndef METAMORPHIC_DIST
        ///TODO: Validation Layers
        //createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        //createInfo.ppEnabledLayerNames = validationLayers.data();
        createInfo.enabledLayerCount = 0;
    #else
        createInfo.enabledLayerCount = 0;
    #endif
        return RenderAPIError::None;
    }
    
    bool VulkanRenderer::IsDeviceSuitable(VkPhysicalDevice device)const noexcept{
        QueueFamilyIndices indices = FindQueueFamilies(device);

        return indices.IsComplete();
    }
    QueueFamilyIndices VulkanRenderer::FindQueueFamilies(VkPhysicalDevice device)const noexcept{
        QueueFamilyIndices indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for(const auto& queueFamily : queueFamilies){
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
                indices.m_GraphicsFamily = i;
            }

            if(indices.IsComplete())break;
            i++;
        }
        return indices;
    }
    RenderAPIError VulkanRenderer::Shutdown()noexcept{
        vkDestroyInstance(m_Instance, nullptr);
        return RenderAPIError::None;
    }

    void VulkanRenderer::PrepareScreen() noexcept{

    }
    void VulkanRenderer::ClearDepthBuffers()noexcept{

    }

    void VulkanRenderer::Update()noexcept{}
}