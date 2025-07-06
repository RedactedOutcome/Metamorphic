#pragma once

#include "Metamorphic/pch.h"

namespace Metamorhpic{
    class Texture{
    public:
        Texture()noexcept;
        ~Texture()noexcept;
    public:
        uint32_t GetTextureId() const noexcept{return m_TextureId;}
        bool IsCreated() const noexcept{return m_IsCreated;}
    private:
        uint32_t m_TextureId = 0;
        bool m_IsCreated = false;
    };
}