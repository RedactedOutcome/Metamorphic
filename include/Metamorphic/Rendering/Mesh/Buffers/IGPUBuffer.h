#pragma once

#include "BufferData.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    struct GPUBufferVTable{
        std::function<void(IGPUBuffer*)> m_Bind;
        std::function<void(IGPUBuffer*)> m_Create;
        std::function<void(IGPUBuffer*)> m_CleanUp;
        std::function<void(IGPUBuffer*, const void* data, size_t size, BufferDataType type, void* meta)> m_UploadData;
    };
    class METAMORPHIC_API IGPUBuffer{
    public:
        IGPUBuffer()noexcept;
        virtual ~IGPUBuffer()noexcept;

    public:
        void* GetMetadata()const noexcept{return m_Metadata;}
        BufferDataType GetBufferDataType() const noexcept{return m_DataType;}
    private:
        void* m_Metadata=nullptr;
        BufferDataType m_DataType=BufferDataType::Float;
        uint32_t m_VTableType = 0;
    };
}