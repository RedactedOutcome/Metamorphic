#pragma once

#include "Rendering/Shader/Shader.h"

namespace Metamorphic{
    class METAMORPHIC_API DirectX12Shader : public Shader{
    public:
        DirectX12Shader(IRenderAPI* renderAPI)noexcept;
        ~DirectX12Shader()noexcept;

        void Start()noexcept override;
        void Stop()noexcept override;
    };
}