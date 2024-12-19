#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    enum class RenderAPI{
        None=0,
        OpenGL,
        DirectX12
    };

    class MORPHIC_API RendererAPI{
    public:
        //Depending on the renderapi we compile with will allocate
        static RendererAPI* CreateRenderAPI();

        RendererAPI(RenderAPI m_API);
        ~RendererAPI();

        virtual void Init();
        virtual void Shutdown();

        virtual void PrepareDraw();
        virtual void ClearDepthBuffer();

        const RenderAPI GetRenderAPI() const noexcept{return m_API;}
    protected:
        RenderAPI m_API = RenderAPI::None;
    };
}