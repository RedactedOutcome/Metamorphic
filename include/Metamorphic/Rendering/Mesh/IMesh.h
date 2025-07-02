#pragma once

#include "MeshData/MeshData.h"
#include "Metamorphic/Rendering/IRenderAPI.h"
#include "Buffers/IGPUBuffer.h"

namespace Metamorphic{
    class METAMORPHIC_API IMesh{
    public:
        IMesh()noexcept;
        IMesh(IRenderAPI* renderAPI)noexcept;
        IMesh(IRenderAPI* renderAPI, MeshData* meshData)noexcept;
        virtual ~IMesh()noexcept;

        virtual void Create()noexcept=0;
        virtual void Draw()noexcept=0;
        virtual void CleanUp()noexcept=0;
    public:
        void SetRenderAPI(IRenderAPI* renderAPI)noexcept;
        /// @brief simply resets m_MeshData without modifying the mesh
        void SetMeshData(MeshData* meshData)noexcept;
    public:
        bool IsCreated()const noexcept{return m_IsCreated;}
        int32_t GetMeshId() const noexcept{return m_MeshId;}
        IRenderAPI* GetRenderAPI() const noexcept{return m_RenderAPI;}
        MeshData* GetMeshData() const noexcept{return m_MeshData;}
    protected:
        bool m_IsCreated=false;
        int32_t m_MeshId = -1;
        IRenderAPI* m_RenderAPI=nullptr;
        MeshData* m_MeshData=nullptr;
    };
}