#include "Metamorphic/pch.h"
#include "Rendering/Shader/Shader.h"

namespace Metamorphic{
    Shader::Shader()noexcept{}
    Shader::Shader(IRenderAPI* renderAPI)noexcept : m_RenderAPI(renderAPI){}
    Shader::~Shader()noexcept{}

    void Shader::Start()noexcept{}
    void Shader::Stop()noexcept{}

    void Shader::SetRenderAPI(IRenderAPI* renderAPI)noexcept{m_RenderAPI = renderAPI;}
}