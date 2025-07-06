#include "Metamorphic/pch.h"
#include "Rendering/IRenderAPI.h"
#include "Platform/Rendering/Shaders/OpenGLShader.h"

namespace Metamorphic{
    OpenGLShader::OpenGLShader(IRenderAPI* renderAPI) noexcept : Shader(renderAPI){}

    void OpenGLShader::Start()noexcept{}
    void OpenGLShader::Stop()noexcept{}
}