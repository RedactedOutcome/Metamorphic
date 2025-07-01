#pragma once

#include "IMesh.h"

namespace Metamorphic{
    class BasicMesh{
    public:
        BasicMesh()noexcept;
        BasicMesh(IRenderAPI* renderAPI)noexcept;
        BasicMesh(IRenderAPI* renderAPI, IMeshData* meshData)noexcept;
        ~BasicMesh()override;

        void Draw()noexcept override;
        void CleanUp()noexcept override;
    };
}