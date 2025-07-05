#include "Metamorphic/pch.h"
#include "Rendering/Shader/Data/ShaderData.h"

namespace Metamorphic{
    ShaderData::ShaderData()noexcept{}
    ShaderData::ShaderData(HBuffer&& vertexShaderData, HBuffer&& fragmentShaderData)noexcept:
        m_VertexShaderData(vertexShaderData), m_FragmentShaderData(fragmentShaderData){}
    ShaderData::~ShaderData()noexcept{}

    void ShaderData::SetVertexShaderData(const HBuffer& data){
        m_VertexShaderData = data;
    }
    void ShaderData::SetVertexShaderData(HBuffer&& data){
        m_VertexShaderData = std::move(data);
    }
    void ShaderData::SetFragmentShaderData(const HBuffer& data){
        m_FragmentShaderData = data;
    }
    void ShaderData::SetFragmentShaderData(HBuffer&& data){
        m_FragmentShaderData = std::move(data);
    }
}