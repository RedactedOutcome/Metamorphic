#include "Metamorphic/pch.h"

#include "Rendering/Mesh/TexturedMeshData.h"
namespace Metamorphic{
    void TexturedMeshData::SetTextureCoordBufferType(BufferType type)noexcept{
        m_TextureCoordBufferType = type;
    }
    void TexturedMeshData::SetTextureCoordData(void* data, size_t count)noexcept{
        m_TextureCoordData = data;
        m_TextureCoordCount = count;
    }
}