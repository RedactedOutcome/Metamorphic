#pragma once

#include "../MeshData/BufferTypes.h"

namespace Metamorphic{
    class IGPUBuffer{
    public:
        IGPUBuffer()noexcept;
        virtual ~IGPUBuffer()noexcept;

        virtual void Bind()noexcept=0;
        virtual void Create()noexcept=0;
        virtual void UploadData(const void* data, size_t size, BufferType type)noexcept=0;
    public:
        void* GetMetadata()const noexcept{return m_Metadata;}
    private:
        void* m_Metadata=nullptr;
        BufferType m_Type=BufferType::Float;
    };
}