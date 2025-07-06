#pragma once

#include "Rendering/Shader/Shader.h"

namespace Metamorphic{
    class METAMORPHIC_API OpenGLShader : public Shader{
    public:
        OpenGLShader(IRenderAPI* renderAPI)noexcept;
        ~OpenGLShader()noexcept;

        void Start()noexcept override;
        void Stop()noexcept override;
    };
}