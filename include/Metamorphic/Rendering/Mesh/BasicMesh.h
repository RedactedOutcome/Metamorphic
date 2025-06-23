#pragma once

#include "IMesh.h"

namespace Metamorphic{
    template <typename VertexType=float, typename IndexType=uint32_t>
    class BasicMesh : public IMesh<VertexType, IndexType>{
    public:
        BasicMesh()noexcept{}

        void Create(VertexType* vertices, IndexType* indices, uint32_t vertexCount, uint32_t indexCount)noexcept{
            
            m_IsCreated = true;
        }
        void Draw()noexcept override{

        }
        void CleanUp()noexcept override{

        }
    };
}