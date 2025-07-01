#pragma once

#include "IMeshData.h"

namespace Metamorphic{
    class TexturedMeshData : public IMeshData{
    public:
        TexturedMeshData()noexcept{}

        void SetTextureCoordBufferType(BufferType type)noexcept;
        void SetTextureCoordData(void* data, size_t count)noexcept;
    public:
        BufferType GetTextureCoordBufferType()const noexcept{return m_TextureCoordBufferType;}
        void* GetTextureCoordData() const noexcept{return m_TextureCoordData;}
        size_t GetTextureCoordCount()const noexcept{return m_TextureCoordCount;}
    private:
        BufferType m_TextureCoordBufferType=BufferType::Float;
        void* m_TextureCoordData = nullptr;
        size_t m_TextureCoordCount = 0;
    };
}