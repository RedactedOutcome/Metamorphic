#include "Metamorphic/pch.h"
#include "Rendering/Mesh/Buffers/IGPUBuffer.h"

namespace Metamorphic{
    IGPUBuffer::IGPUBuffer()noexcept{}
    IGPUBuffer::~IGPUBuffer()noexcept{}
    void IGPUBuffer::SetBind(std::function<void(IGPUBuffer*)> bind)noexcept{
        m_Bind = bind;
    }
    void IGPUBuffer::SetCreate(std::function<void(IGPUBuffer*)> create)noexcept{
        m_Create = create;
    }
    void IGPUBuffer::SetCleanUp(std::function<void(IGPUBuffer*)> cleanUp)noexcept{
        m_CleanUp = cleanUp;
    }
    void IGPUBuffer::SetUploadData(std::function<void(IGPUBuffer*, const void*, size_t, BufferDataType, void*)> uploadData)noexcept{
        m_UploadData = uploadData;
    }
    
}