#include "Metamorphic/pch.h"
#include "Platform/Renderers/OpenGLRenderer.h"
#include "Core/Logger.h"

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