#include "Metamorphic/pch.h"
#include "Platform/Rendering/Renderers/MetalRenderer.h"
#include "Core/Logger.h"

namespace Metamorphic{
    MetalRenderer::MetalRenderer(IWindow* window)noexcept: IRenderAPI(window){}
    MetalRenderer::~MetalRenderer()noexcept {}

    RenderAPIError MetalRenderer::Init()noexcept{return RenderAPIError::None;}
    RenderAPIError MetalRenderer::Shutdown()noexcept{return RenderAPIError::None;}

    void MetalRenderer::PrepareScreen()noexcept{}
    void MetalRenderer::ClearDepthBuffers()noexcept{}
    void MetalRenderer::Update()noexcept{}
}