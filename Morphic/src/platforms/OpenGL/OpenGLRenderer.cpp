#include "Morphic/pch.h"
#include "Morphic/Rendering/RenderAPIS/OpenGLRenderer.h"
#include "Morphic/Application.h"

namespace Morphic{
    RendererAPI* RendererAPI::CreateRenderAPI() MORPHIC_NOEXCEPT{
        return new OpenGLRenderer();
    }
    OpenGLRenderer::OpenGLRenderer(): RendererAPI(RenderAPI::OpenGL){}
    OpenGLRenderer::~OpenGLRenderer(){}

    void OpenGLRenderer::Init(){

    }    
    void OpenGLRenderer::Shutdown(){}    

    void OpenGLRenderer::PrepareDraw(){}    
    void OpenGLRenderer::ClearDepthBuffer(){}    
}