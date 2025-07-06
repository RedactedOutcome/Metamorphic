#include "Metamorphic/pch.h"
#include "Rendering/IRenderAPI.h"
#include "Platform/Rendering/Shaders/DirectX12Shader.h"

namespace Metamorphic{
    DirectX12Shader::DirectX12Shader(IRenderAPI* renderAPI) noexcept : Shader(renderAPI){}

    void DirectX12Shader::Start()noexcept{}
    void DirectX12Shader::Stop()noexcept{}
}