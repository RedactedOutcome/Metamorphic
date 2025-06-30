#include "Metamorphic/pch.h"
#include "Metamorphic/Rendering/Mesh/IMeshData.h"

namespace Metamorphic{
    IMeshData::IMeshData()noexcept{}
    IMeshData::~IMeshData()noexcept{}
    IMeshData::IMeshData(BufferType vertexType, BufferType indexType)noexcept:
        m_VertexBufferType(vertexType), m_IndexBufferType(indexType){}
    
    void IMeshData::SetVertexBufferType(BufferType type)noexcept{m_VertexBufferType = type;}
    void IMeshData::SetIndexBufferType(BufferType type)noexcept{m_IndexBufferType = type;}
    void IMeshData::SetVertexData(void* vertexData, size_t count)noexcept{
        m_VertexData = vertexData;
        m_VertexCount = count;
    }
    void IMeshData::SetIndexData(void* indexData, size_t count)noexcept{
        m_IndexData = indexData;
        m_IndexCount = count;
    }

    void IMeshData::SetBufferTypes(BufferType vertexType, BufferType indexType)noexcept{
        m_VertexBufferType = vertexType;
        m_IndexBufferType = indexType;
    }
}