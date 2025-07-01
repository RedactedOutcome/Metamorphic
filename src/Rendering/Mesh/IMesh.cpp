#include "Metamorphic/pch.h"
#include "Metamorphic/Rendering/Mesh/IMesh.h"

namespace Metamorphic{
    IMesh::IMesh()noexcept{}
    IMesh::IMesh(IRenderAPI* renderAPI)noexcept : m_RenderAPI(renderAPI){}
    IMesh::IMesh(IRenderAPI* renderAPI, IMeshData* meshData)noexcept: m_RenderAPI(renderAPI), m_MeshData(meshData){}
    IMesh::~IMesh()noexcept{}

    void IMesh::SetMeshData(IMeshData* meshData)noexcept{
        m_MeshData = meshData;
    }
}