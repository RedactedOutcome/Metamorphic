#include "Metamorphic/pch.h"
#include "Core/Logger.h"
#include "Platform/Rendering/Renderers/MetalRenderer.h"
#include "Platform/Rendering/Shaders/MetalShader.h"
namespace Metamorphic{
    MetalRenderer::MetalRenderer(IWindow* window)noexcept: IRenderAPI(window){}
    MetalRenderer::~MetalRenderer()noexcept {}

    RenderAPIError MetalRenderer::Init()noexcept{return RenderAPIError::None;}
    RenderAPIError MetalRenderer::Shutdown()noexcept{return RenderAPIError::None;}

    void MetalRenderer::PrepareScreen()noexcept{}
    void MetalRenderer::ClearDepthBuffers()noexcept{}
    void MetalRenderer::Update()noexcept{}

    std::unique_ptr<Shader> MetalRenderer::CreateShader()noexcept{
        return std::make_unique<MetalShader>(this);
    }
}