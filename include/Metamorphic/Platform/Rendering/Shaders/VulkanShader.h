#pragma once

#include "Rendering/Shader/Shader.h"

namespace Metamorphic{
    class METAMORPHIC_API VulkanShader : public Shader{
    public:
        VulkanShader(IRenderAPI* renderAPI)noexcept;
        ~VulkanShader()noexcept;

        void Start()noexcept override;
        void Stop()noexcept override;
    };
}