#include "Metamorphic/pch.h"
#include "Metamorphic/Rendering/Mesh/MeshData/MeshData.h"

namespace Metamorphic{
    MeshData::MeshData()noexcept{}
    MeshData::~MeshData()noexcept{}
    MeshData::MeshData(BufferDataType vertexType, BufferDataType indexType)noexcept:
        m_VertexBufferDataType(vertexType), m_IndexBufferDataType(indexType){}
    
    void MeshData::SetVertexBufferDataType(BufferDataType type)noexcept{m_VertexBufferDataType = type;}
    void MeshData::SetIndexBufferDataType(BufferDataType type)noexcept{m_IndexBufferDataType = type;}
    void MeshData::SetVertexData(void* vertexData, size_t count)noexcept{
        m_VertexData = vertexData;
        m_VertexCount = count;
    }
    void MeshData::SetIndexData(void* indexData, size_t count)noexcept{
        m_IndexData = indexData;
        m_IndexCount = count;
    }

    void MeshData::SetBufferDataTypes(BufferDataType vertexType, BufferDataType indexType)noexcept{
        m_VertexBufferDataType = vertexType;
        m_IndexBufferDataType = indexType;
    }
}