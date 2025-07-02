#include "Metamorphic/pch.h"
#include "Rendering/Mesh/MeshData/TexturedMeshData.h"

namespace Metamorphic{
    void TexturedMeshData::SetTextureCoordBufferDataType(BufferDataType type)noexcept{
        m_TextureCoordBufferDataType = type;
    }
    void TexturedMeshData::SetTextureCoordData(void* data, size_t count)noexcept{
        m_TextureCoordData = data;
        m_TextureCoordCount = count;
    }
}