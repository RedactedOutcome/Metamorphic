#include "Metamorphic/pch.h"
#include "Rendering/Shader/Data/ShaderData.h"
#include "Rendering/IRenderAPI.h"

namespace Metamorphic{
    ShaderData::ShaderData()noexcept{}
    ShaderData::ShaderData(HBuffer&& vertexShaderData, HBuffer&& fragmentShaderData)noexcept:
        m_VertexShaderData(vertexShaderData), m_FragmentShaderData(fragmentShaderData){}
    ShaderData::ShaderData(const HBuffer& vertexShaderData, HBuffer&& fragmentShaderData)noexcept:
        m_VertexShaderData(vertexShaderData), m_FragmentShaderData(fragmentShaderData){}
    ShaderData::ShaderData(const HBuffer& vertexShaderData, const HBuffer& fragmentShaderData)noexcept:
        m_VertexShaderData(vertexShaderData), m_FragmentShaderData(fragmentShaderData){}
    ShaderData::ShaderData(HBuffer&& vertexShaderData, const HBuffer& fragmentShaderData)noexcept:
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

    ResourceManagerError ShaderData::LoadResource(IRenderAPI* renderAPI, const HBuffer& filePath)noexcept{
        std::filesystem::path path(filePath.GetSafeCString().GetCStr());
        switch(renderAPI->GetRenderAPI()){
        case RenderAPI::OpenGL:{
            path.replace_extension(".glsl");
            break;
        }
        default:
            return ResourceManagerError::UnsupportedAPI;
        }
        ResourceManagerError error = ResourceManager::LoadResource(ResourceType::ShaderData, path, m_VertexShaderData);
        if(error != ResourceManagerError::None)return error;

        error = ResourceManager::LoadResource(ResourceType::ShaderData, path, m_FragmentShaderData);
        if(error != ResourceManagerError::None)return error;

        return ResourceManagerError::None;
    }
}