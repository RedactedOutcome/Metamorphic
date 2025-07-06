#pragma once

#include "Rendering/Shader/Shader.h"

namespace Metamorphic{
    class METAMORPHIC_API MetalShader : public Shader{
    public:
        MetalShader(IRenderAPI* renderAPI)noexcept;
        ~MetalShader()noexcept;

        void Start()noexcept override;
        void Stop()noexcept override;
    };
}