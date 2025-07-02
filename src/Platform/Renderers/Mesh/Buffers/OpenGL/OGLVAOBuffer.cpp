#include "Metamorphic/pch.h"
#include "Platform/Renderers/Mesh/Buffers/OpenGL/OGLVAOBuffer.h"
#include "Core/Logger.h"

namespace Metamorphic{
    OGLVAOBuffer::OGLVAOBuffer()noexcept{}
    OGLVAOBuffer::~OGLVAOBuffer()noexcept{
        MORPHIC_DEBUG("Deconstructing OpenGL VAO Buffer");
    }

    void OGLVAOBuffer::Bind()noexcept{}
    void OGLVAOBuffer::Create()noexcept{}
    void OGLVAOBuffer::CleanUp()noexcept{}

    void OGLVAOBuffer::UploadData(const void* data, size_t size, BufferType type, void* meta)noexcept{

    }
}