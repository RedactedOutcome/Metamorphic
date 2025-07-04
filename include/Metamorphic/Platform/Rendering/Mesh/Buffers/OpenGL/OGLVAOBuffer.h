#pragma once

#include "Metamorphic/Rendering/Mesh/Buffers/IGPUBuffer.h"
#include "Metamorphic/pch.h"

namespace Metamorphic{
    class METAMORPHIC_API OGLVAOBuffer : public IGPUBuffer{
    public:
        OGLVAOBuffer()noexcept;
        ~OGLVAOBuffer()noexcept override;

        void Bind()noexcept;
        void Create()noexcept;
        void CleanUp()noexcept;
        
        void UploadData(const void* data, size_t size, BufferDataType type, void* meta)noexcept;
    private:
        uint32_t GetVaoId() const noexcept;
    };
}