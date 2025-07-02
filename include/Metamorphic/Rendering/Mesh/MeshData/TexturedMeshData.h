#pragma once

#include "MeshData.h"

namespace Metamorphic{
    class METAMORPHIC_API TexturedMeshData : public MeshData{
    public:
        TexturedMeshData()noexcept{}

        void SetTextureCoordBufferDataType(BufferDataType type)noexcept;
        void SetTextureCoordData(void* data, size_t count)noexcept;
    public:
        BufferDataType GetTextureCoordBufferDataType()const noexcept{return m_TextureCoordBufferDataType;}
        void* GetTextureCoordData() const noexcept{return m_TextureCoordData;}
        size_t GetTextureCoordCount()const noexcept{return m_TextureCoordCount;}
    private:
        BufferDataType m_TextureCoordBufferDataType=BufferDataType::Float;
        void* m_TextureCoordData = nullptr;
        size_t m_TextureCoordCount = 0;
    };
}