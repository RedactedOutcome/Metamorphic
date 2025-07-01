#pragma once

#include "MeshData/IMeshData.h"
#include "Metamorphic/Rendering/IRenderAPI.h"

namespace Metamorphic{
    class IMesh{
    public:
        IMesh()noexcept;
        IMesh(IRenderAPI* renderAPI)noexcept;
        IMesh(IRenderAPI* renderAPI, IMeshData* meshData)noexcept;
        virtual ~IMesh()noexcept;

        void Draw()noexcept=0;
        void CleanUp()noexcept=0;
    public:
        /// @brief simply resets m_MeshData without modifying the mesh
        void SetMeshData(IMeshData* meshData)noexcept;
    public:
        bool IsCreated()const noexcept{return m_IsCreated;}
        int32_t GetMeshId() const noexcept{return m_MeshId;}
        IRenderAPI* GetRenderAPI() const noexcept{return m_RenderAPI;}
        IMeshData* GetMeshData() const noexcept{return m_MeshData;}
    protected:
        bool m_IsCreated=false;
        int32_t m_MeshId = -1;
        IRenderAPI* m_RenderAPI=nullptr;
        IMeshData* m_MeshData=nullptr;
    };
}