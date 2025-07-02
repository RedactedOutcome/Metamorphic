#include "Metamorphic/pch.h"
#include "Metamorphic/Rendering/Mesh/BasicMesh.h"
#include "Core/Logger.h"

namespace Metamorphic{
    BasicMesh::BasicMesh()noexcept{}
    BasicMesh::BasicMesh(IRenderAPI* renderAPI)noexcept : IMesh(renderAPI){}
    BasicMesh::BasicMesh(IRenderAPI* renderAPI, MeshData* meshData)noexcept: IMesh(renderAPI){}
    BasicMesh::~BasicMesh()noexcept{}

    void BasicMesh::Create()noexcept{
        MORPHIC_DEBUG("Creating Mesh");

        
    }
    void BasicMesh::Draw()noexcept{
    }
    void BasicMesh::CleanUp()noexcept{
    }
}