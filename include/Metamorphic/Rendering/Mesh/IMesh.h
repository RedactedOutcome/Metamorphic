#pragma once

#include "Metamorphic/pch.h"

namespace Metamorphic{
    template <typename VertexType=float, typename IndexType=uint32_t>
    class IMesh{
    public:
        Mesh()noexcept{}
        ~Mesh()noexcept{}

        virtual void Draw()noexcept=0;
        virtual void CleanUp()noexcept=0;
    public:
        bool IsCreated()const noexcept{return m_IsCreated;}
        uint32_t GetVertexCount()const noexcept{return m_VertexCount;}
        uint32_t GetIndexCount() const noexcept{return m_IndexCount;}
    protected:
        bool m_IsCreated = false;
        uint32_t m_VertexCount=0;
        uint32_t m_IndexCount=0;
    };
}