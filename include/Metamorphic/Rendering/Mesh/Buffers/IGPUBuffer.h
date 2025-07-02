#pragma once

#include "../MeshData/BufferTypes.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    class METAMORPHIC_API IGPUBuffer{
    public:
        IGPUBuffer()noexcept;
        virtual ~IGPUBuffer()noexcept;

        /// @brief Some buffer types need to be bound/started
        virtual void Bind()noexcept=0;
        /// @brief abstracted api to create a buffer.
        virtual void Create()noexcept=0;
        virtual void CleanUp()noexcept=0;
        /// @brief 
        /// @param data 
        /// @param size 
        /// @param type 
        /// @param meta extra metadata for uploading data to gpu. May or may not modify m_Metadata
        virtual void UploadData(const void* data, size_t size, BufferDataType type, void* meta)noexcept=0;
    public:
        void* GetMetadata()const noexcept{return m_Metadata;}
        BufferDataType GetBufferDataType() const noexcept{return m_DataType;}
    private:
        void* m_Metadata=nullptr;
        BufferDataType m_DataType=BufferDataType::Float;
    };
}