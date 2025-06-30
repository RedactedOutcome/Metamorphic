#pragma once

#include "Metamorphic/pch.h"

namespace Metamorphic{
    enum class BufferType{
        Float = 0,
        UInt8,
        Int8,
        UInt16,
        Int16,
        UInt32,
        Int32
    };
    class IMeshData{
    public:
        IMeshData()noexcept;
        ~IMeshData()noexcept;
        IMeshData(BufferType vertexType, BufferType indexType)noexcept;

        void SetVertexBufferType(BufferType type)noexcept;
        void SetIndexBufferType(BufferType type)noexcept;
        void SetVertexData(void* vertexData, size_t count)noexcept;
        void SetIndexData(void* indexData, size_t count)noexcept;
    public:
        void SetBufferTypes(BufferType vertexType, BufferType indexType)noexcept;
    public:
        bool IsCreated()const noexcept{return m_IsCreated;}
        void* GetVertexData() const noexcept{return m_VertexData;}
        void* GetIndexData() const noexcept{return m_IndexData;}
        uint32_t GetVertexCount()const noexcept{return m_VertexCount;}
        uint32_t GetIndexCount() const noexcept{return m_IndexCount;}
        BufferType GetVertexBufferType() const noexcept{return m_VertexBufferType;}
        BufferType GetIndexBufferType() const noexcept{return m_IndexBufferType;}
        void* GetMetadata()const noexcept{return m_Metadata;}
    protected:
        bool m_IsCreated = false;
        BufferType m_VertexBufferType=BufferType::Float;
        BufferType m_IndexBufferType=BufferType::UInt32;
        void* m_VertexData = nullptr;
        void* m_IndexData = nullptr;
        uint32_t m_VertexCount=0;
        uint32_t m_IndexCount=0;
        void* m_Metadata=nullptr;
    };
}