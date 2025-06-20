#include "Metamorphic/pch.h"
#include "Platform/Renderers/OpenGLRenderer.h"

namespace Metamorphic{
    OpenGLRenderer::OpenGLRenderer(IWindow* window)noexcept : IRenderAPI(window){}
    OpenGLRenderer::~OpenGLRenderer()noexcept {}

    RenderAPIError OpenGLRenderer::Init()noexcept{
        m_Window->CreateOpenGLBindings();
        return RenderAPIError::None;
    }
    RenderAPIError OpenGLRenderer::Shutdown()noexcept{
        return RenderAPIError::None;
    }

    void OpenGLRenderer::PrepareScreen() noexcept{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRenderer::ClearDepthBuffers()noexcept{

    }
}