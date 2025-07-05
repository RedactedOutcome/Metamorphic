#pragma once

#include "Metamorphic/Rendering/IRenderAPI.h"
#include "Data/ShaderData.h"

namespace Metamorphic{
    class Shader{
    public:
        Shader()noexcept;
        Shader(IRenderAPI* renderAPI)noexcept;
        ~Shader()noexcept;

        virtual void Start()noexcept=0;
        virtual void Stop()noexcept=0;
    public:
        /// @brief Strictly changes m_RenderAPI
        void SetRenderAPI(IRenderAPI* renderAPI)noexcept;
    public:
        IRenderAPI* GetRenderAPI() const noexcept{return m_RenderAPI;}
        uint32_t GetShaderId()const noexcept{return m_ShaderId;}
        bool IsCreated() const noexcept{return m_IsCreated;}
    protected:
        IRenderAPI* m_RenderAPI = nullptr;
        uint32_t m_ShaderId=0;
        bool m_IsCreated = false;
    };
}