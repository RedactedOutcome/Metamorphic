#include "Metamorphic/pch.h"
#include "Rendering/IRenderAPI.h"


namespace Metamorphic{
    IRenderAPI::IRenderAPI(IWindow* window) noexcept : m_Window(window), m_RenderAPI(RenderAPI::OpenGL){}
    IRenderAPI::~IRenderAPI()noexcept{}

    RenderAPIError IRenderAPI::Init()noexcept{return RenderAPIError::None;}
    RenderAPIError IRenderAPI::Shutdown()noexcept{return RenderAPIError::None;}

    void IRenderAPI::PrepareScreen()noexcept{}
    void IRenderAPI::ClearDepthBuffers()noexcept{}
    void IRenderAPI::Update()noexcept{}


    uint32_t IRenderAPI::GenerateShaderId()noexcept{
        return 0;
    }
    std::unique_ptr<Shader> IRenderAPI::CreateShader()noexcept{
        return nullptr;
    }
}