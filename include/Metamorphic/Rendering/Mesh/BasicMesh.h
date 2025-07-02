#pragma once

#include "IMesh.h"

namespace Metamorphic{
    class METAMORPHIC_API BasicMesh : public IMesh{
    public:
        BasicMesh()noexcept;
        BasicMesh(IRenderAPI* renderAPI)noexcept;
        BasicMesh(IRenderAPI* renderAPI, MeshData* meshData)noexcept;
        ~BasicMesh()override;
        
        void Create()noexcept override;
        void Draw()noexcept override;
        void CleanUp()noexcept override;
    private:
        IGPUBuffer* m_VertexBuffer=nullptr;
    };
}