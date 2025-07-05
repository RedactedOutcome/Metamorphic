#pragma once

#include "Data/ShaderData.h"

namespace Metamorphic{
    class IRenderAPI;
    class METAMORPHIC_API Shader{
    public:
        Shader()noexcept;
        Shader(IRenderAPI* renderAPI)noexcept;
        Shader(IRenderAPI* renderAPI, ShaderData* shaderData)noexcept;
        ~Shader()noexcept;

        virtual void Start()noexcept=0;
        virtual void Stop()noexcept=0;
    public:
        /// @brief Strictly changes m_RenderAPI
        void SetRenderAPI(IRenderAPI* renderAPI)noexcept;
        void SetShaderData(ShaderData* shaderData)noexcept;
    public:
        IRenderAPI* GetRenderAPI() const noexcept{return m_RenderAPI;}
        ShaderData* GetShaderData() const noexcept{return m_ShaderData;}
        uint32_t GetShaderId()const noexcept{return m_ShaderId;}
        bool IsCreated() const noexcept{return m_IsCreated;}
    protected:
        IRenderAPI* m_RenderAPI = nullptr;
        ShaderData* m_ShaderData = nullptr;
        uint32_t m_ShaderId=0;
        bool m_IsCreated = false;
    };
}