#include "Metamorphic/pch.h"
#include "Rendering/IRenderAPI.h"
#include "Platform/Rendering/Shaders/MetalShader.h"

namespace Metamorphic{
    MetalShader::MetalShader(IRenderAPI* renderAPI) noexcept : Shader(renderAPI){}

    void MetalShader::Start()noexcept{}
    void MetalShader::Stop()noexcept{}
}