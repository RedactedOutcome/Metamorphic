#include "Metamorphic/pch.h"
#include "Rendering/IRenderAPI.h"
#include "Platform/Rendering/Shaders/VulkanShader.h"

namespace Metamorphic{
    VulkanShader::VulkanShader(IRenderAPI* renderAPI) noexcept : Shader(renderAPI){}
    VulkanShader::~VulkanShader()noexcept{}

    void VulkanShader::Start()noexcept{}
    void VulkanShader::Stop()noexcept{}
}