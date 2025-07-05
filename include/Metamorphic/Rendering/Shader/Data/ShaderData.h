#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    class METAMORPHIC_API ShaderData{
    public:
        ShaderData()noexcept;
        ShaderData(HBuffer&& vertexShaderData, HBuffer&& fragmentShaderData)noexcept;
        ~ShaderData()noexcept;

        void SetVertexShaderData(const HBuffer& data)noexcept;
        void SetVertexShaderData(HBuffer&& data)noexcept;
        void SetFragmentShaderData(const HBuffer& data)noexcept;
        void SetFragmentShaderData(HBuffer&& data)noexcept;
    public:
        HBuffer GetVertexShaderData() const noexcept{return m_VertexShaderData;}
        HBuffer GetFragmentShaderData() const noexcept{return m_FragmentShaderData;}
    private:
        HBuffer m_VertexShaderData = "";
        HBuffer m_FragmentShaderData = "";
    };
}