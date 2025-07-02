#include "Metamorphic/pch.h"
#include "Metamorphic/Rendering/Mesh/IMesh.h"

namespace Metamorphic{
    IMesh::IMesh()noexcept{}
    IMesh::IMesh(IRenderAPI* renderAPI)noexcept : m_RenderAPI(renderAPI){}
    IMesh::IMesh(IRenderAPI* renderAPI, MeshData* meshData)noexcept: m_RenderAPI(renderAPI), m_MeshData(meshData){}
    IMesh::~IMesh()noexcept{}

    void IMesh::SetRenderAPI(IRenderAPI* renderAPI)noexcept{
        m_RenderAPI = renderAPI;
    }
    void IMesh::SetMeshData(MeshData* meshData)noexcept{
        m_MeshData = meshData;
    }

    void IMesh::Create()noexcept{}
    void IMesh::Draw()noexcept{}
    void IMesh::CleanUp()noexcept{}
}