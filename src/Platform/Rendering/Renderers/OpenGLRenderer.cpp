#include "Metamorphic/pch.h"
#include "Platform/Rendering/Renderers/OpenGLRenderer.h"
#include "Core/Logger.h"

#include "Platform/Rendering/Mesh/Buffers/OpenGL/OGLVAOBuffer.h"

namespace Metamorphic{
    OpenGLRenderer::OpenGLRenderer(IWindow* window)noexcept : IRenderAPI(window){}
    OpenGLRenderer::~OpenGLRenderer()noexcept {}

    RenderAPIError OpenGLRenderer::Init()noexcept{
        MORPHIC_DEBUG("Initializing OpenGLRenderer");
        m_Window->CreateOpenGLBindings();
        if(glewInit() != GLEW_OK){
            return RenderAPIError::FailedToInitializeOpenGL;
        }
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

        m_GPUVTables.reserve(3);
        /// @brief Empty Buffer
        GPUBufferVTable table;
        table.m_Bind = [](IGPUBuffer* buff){};
        table.m_CleanUp = [](IGPUBuffer* buff){};
        table.m_Create = [](IGPUBuffer* buff){};
        table.m_UploadData = [](IGPUBuffer* buff, const void* data, size_t size, BufferDataType type, void* meta){};
        m_GPUVTables.emplace_back(table);

        /// @brief VAO Buffer
        table.m_Bind = [](IGPUBuffer* buff){
            reinterpret_cast<OGLVAOBuffer*>(buff)->Bind();
        };
        table.m_CleanUp = [](IGPUBuffer* buff){
            reinterpret_cast<OGLVAOBuffer*>(buff)->CleanUp();
        };
        table.m_Create = [](IGPUBuffer* buff){
            reinterpret_cast<OGLVAOBuffer*>(buff)->Create();
        };
        table.m_UploadData = [](IGPUBuffer* buff, const void* data, size_t size, BufferDataType type, void* meta){
            reinterpret_cast<OGLVAOBuffer*>(buff)->UploadData(data, size, type, meta);
        };
        m_GPUVTables.emplace_back(table);
        /// @brief VBO Buffer
        return RenderAPIError::None;
    }
    RenderAPIError OpenGLRenderer::Shutdown()noexcept{
        return RenderAPIError::None;
    }

    void OpenGLRenderer::PrepareScreen() noexcept{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRenderer::ClearDepthBuffers()noexcept{
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::Update()noexcept{}
}