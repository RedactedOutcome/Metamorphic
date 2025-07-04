#pragma once

#include "IWindow.h"
#include "Mesh/Buffers/IGPUBuffer.h"
#include "Shader/Shader.h"

namespace Metamorphic{
    enum class RenderAPI{
        None=0,
        OpenGL
    };
    enum class RenderAPIError{
        None=0,
        FailedToInitializeOpenGL,
        FailedToCreateVulkanInstance,
        FailedToFindGraphicsCard,
        FailedToCreatePhysicalDevice,
        FailedToCreateWindowSurface,
        FailedToFindSupportedGraphicsCard
    };
    class IRenderAPI{
    public:
        IRenderAPI(IWindow* window)noexcept;
        virtual ~IRenderAPI()noexcept;

        virtual RenderAPIError Init()noexcept=0;
        virtual RenderAPIError Shutdown()noexcept=0;
        virtual void PrepareScreen()noexcept=0;
        virtual void ClearDepthBuffers()noexcept=0;
        virtual void Update()noexcept=0;
    public:
        uint32_t GenerateShaderId()noexcept;
        virtual std::unique_ptr<Shader> CreateShader()noexcept=0;
        //void AllocateBufferData(IGPUBuffer* output, void* meta)noexcept;
    public:
        IWindow* GetWindow()const noexcept{return m_Window;}
        RenderAPI GetRenderAPI()const noexcept{return m_RenderAPI;}
        const std::vector<uint32_t>& GetMeshIds()const noexcept{return m_MeshIds;}
    protected:
        IWindow* m_Window = nullptr;
        RenderAPI m_RenderAPI = RenderAPI::None;
        std::vector<uint32_t> m_MeshIds;
        std::vector<GPUBufferVTable> m_GPUVTables;
    };
}