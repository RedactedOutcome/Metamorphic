#include "Metamorphic/pch.h"
#include "Core/Logger.h"
#include "Core/Core.h"

#include "Platform/Rendering/Renderers/VulkanRenderer.h"
#include "Platform/Rendering/Shaders/VulkanShader.h"

#ifdef METAMORPHIC_PLATFORM_WINDOWS
    #include "Platform/Window/WindowsWindow.h"
#else
    #error Unsupported platform for vulkan renderer
#endif
namespace Metamorphic{
    VulkanRenderer::VulkanRenderer(IWindow* window)noexcept : IRenderAPI(window){}
    VulkanRenderer::~VulkanRenderer()noexcept{}

    RenderAPIError VulkanRenderer::Init()noexcept{
        MORPHIC_DEBUG("Initializing Vulkan Renderer");
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

        uint32_t extensionCount = 2;
        const char* extensions[2] = {"VK_KHR_surface", "VK_KHR_win32_surface"};

        instanceCreateInfo.enabledExtensionCount = extensionCount;
        instanceCreateInfo.ppEnabledExtensionNames = extensions;

        if(vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS){
            return RenderAPIError::FailedToCreateVulkanInstance;
        }

        /// Create Window Surface
    #ifdef METAMORPHIC_PLATFORM_WINDOWS
        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

        WindowsWindow* window = reinterpret_cast<WindowsWindow*>(m_Window);
        surfaceCreateInfo.hwnd = window->GetWindow();
        surfaceCreateInfo.hinstance = window->GetInstance();

        if(vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, nullptr, &m_Surface) != VK_SUCCESS){
            return RenderAPIError::FailedToCreateWindowSurface;
        }
        if(m_Surface == VK_NULL_HANDLE){
            return RenderAPIError::FailedToCreateWindowSurface;
        }

    #else
        #error Unsupported platform for vulkan renderer
    #endif
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
        if(m_PhysicalDevice == VK_NULL_HANDLE){
            MORPHIC_ERROR("Failed to find physical device");
            return RenderAPIError::FailedToFindGraphicsCard;
        }
        /// Create Logical Device
        RenderAPIError error = CreateDevice();
        if(error != RenderAPIError::None)return error;
        return RenderAPIError::None;
    }

    RenderAPIError VulkanRenderer::CreateDevice()noexcept{
        QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);
        if(!indices.IsComplete()){
            return RenderAPIError::FailedToFindSupportedGraphicsCard;
        }
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
        if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
            return RenderAPIError::FailedToCreatePhysicalDevice;
        }
        
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.m_GraphicsFamily.value(), indices.m_PresentFamily.value()};

        queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        
        vkGetDeviceQueue(m_Device, indices.m_PresentFamily.value(), 0, &m_PresentQueue);
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
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);
            if (presentSupport) {
                indices.m_PresentFamily = i;
            }
            
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
                indices.m_GraphicsFamily = i;
            }

            if(indices.IsComplete())break;
            i++;
        }
        return indices;
    }
    RenderAPIError VulkanRenderer::Shutdown()noexcept{
        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkDestroyDevice(m_Device, nullptr);
        vkDestroyInstance(m_Instance, nullptr);
        m_Surface = VK_NULL_HANDLE;
        m_Device = VK_NULL_HANDLE;
        m_PhysicalDevice = VK_NULL_HANDLE;
        m_Instance = VK_NULL_HANDLE;
        return RenderAPIError::None;
    }

    void VulkanRenderer::PrepareScreen() noexcept{
        
    }
    void VulkanRenderer::ClearDepthBuffers()noexcept{

    }

    void VulkanRenderer::Update()noexcept{}
    
    std::unique_ptr<Shader> VulkanRenderer::CreateShader()noexcept{
        return std::make_unique<VulkanShader>(reinterpret_cast<IRenderAPI*>(this));
    }
}