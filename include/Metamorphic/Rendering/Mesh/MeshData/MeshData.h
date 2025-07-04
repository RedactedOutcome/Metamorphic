#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"
#include "../Buffers/BufferData.h"

namespace Metamorphic{
    class METAMORPHIC_API MeshData{
    public:
        MeshData()noexcept;
        MeshData(BufferDataType vertexType, BufferDataType indexType)noexcept;
        ~MeshData()noexcept;

        void SetVertexBufferDataType(BufferDataType type)noexcept;
        void SetIndexBufferDataType(BufferDataType type)noexcept;
        void SetVertexData(void* vertexData, size_t count)noexcept;
        void SetIndexData(void* indexData, size_t count)noexcept;
    public:
        void SetBufferDataTypes(BufferDataType vertexType, BufferDataType indexType)noexcept;
    public:
        bool IsCreated()const noexcept{return m_IsCreated;}
        void* GetVertexData() const noexcept{return m_VertexData;}
        void* GetIndexData() const noexcept{return m_IndexData;}
        uint32_t GetVertexCount()const noexcept{return m_VertexCount;}
        uint32_t GetIndexCount() const noexcept{return m_IndexCount;}
        BufferDataType GetVertexBufferDataType() const noexcept{return m_VertexBufferDataType;}
        BufferDataType GetIndexBufferDataType() const noexcept{return m_IndexBufferDataType;}
        void* GetMetadata()const noexcept{return m_Metadata;}
    protected:
        bool m_IsCreated = false;
        BufferDataType m_VertexBufferDataType=BufferDataType::Float;
        BufferDataType m_IndexBufferDataType=BufferDataType::UInt32;
        void* m_VertexData = nullptr;
        void* m_IndexData = nullptr;
        uint32_t m_VertexCount=0;
        uint32_t m_IndexCount=0;
        void* m_Metadata=nullptr;
    };
}