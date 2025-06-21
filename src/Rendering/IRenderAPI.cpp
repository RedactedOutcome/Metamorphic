#include "Metamorphic/pch.h"
#include "Rendering/IRenderAPI.h"

namespace Metamorphic{
    IRenderAPI::IRenderAPI(IWindow* window) noexcept : m_Window(window){}
    IRenderAPI::~IRenderAPI()noexcept{}

    RenderAPIError IRenderAPI::Init()noexcept{return RenderAPIError::None;}
    RenderAPIError IRenderAPI::Shutdown()noexcept{return RenderAPIError::None;}

    void IRenderAPI::PrepareScreen()noexcept{}
    void IRenderAPI::ClearDepthBuffers()noexcept{}
}