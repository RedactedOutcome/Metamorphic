#include "Metamorphic/pch.h"
#include "Platform/Renderers/DirectX12Renderer.h"
#include "Core/Logger.h"

namespace Metamorphic{
    DirectX12Renderer::DirectX12Renderer(IWindow* window)noexcept : IRenderAPI(window){}
    DirectX12Renderer::~DirectX12Renderer()noexcept {}

    RenderAPIError DirectX12Renderer::Init()noexcept{
        MORPHIC_DEBUG("Initializing DirectX12Renderer");
        return RenderAPIError::None;
    }
    RenderAPIError DirectX12Renderer::Shutdown()noexcept{
        return RenderAPIError::None;
    }

    void DirectX12Renderer::PrepareScreen() noexcept{

    }
    void DirectX12Renderer::ClearDepthBuffers()noexcept{

    }

    void DirectX12Renderer::Update()noexcept{}
}