#include "Metamorphic/pch.h"
#include "Rendering/Shader/Data/ShaderData.h"

namespace Metamorphic{
    ShaderData::ShaderData()noexcept{}
    ShaderData::ShaderData(HBuffer&& vertexShaderData, HBuffer&& fragmentShaderData)noexcept:
        m_VertexShaderData(vertexShaderData), m_FragmentShaderData(fragmentShaderData){}
    ShaderData::~ShaderData()noexcept{}

    void ShaderData::SetVertexShaderData(const HBuffer& data)noexcept{
        m_VertexShaderData = data;
    }
    void ShaderData::SetVertexShaderData(HBuffer&& data)noexcept{
        m_VertexShaderData = std::move(data);
    }
    void ShaderData::SetFragmentShaderData(const HBuffer& data)noexcept{
        m_FragmentShaderData = data;
    }
    void ShaderData::SetFragmentShaderData(HBuffer&& data)noexcept{
        m_FragmentShaderData = std::move(data);
    }

    void ShaderData::LoadResource(const HBuffer& filePath)noexcept{
        
    }
}