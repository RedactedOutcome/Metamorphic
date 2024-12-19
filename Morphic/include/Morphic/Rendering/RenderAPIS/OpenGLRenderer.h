#pragma once
#include "../RendererAPI.h"

namespace Morphic{
    class MORPHIC_API OpenGLRenderer : public RendererAPI{
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();

        void Init() override;
        void Shutdown() override;

        void PrepareDraw() override;
        void ClearDepthBuffer() override;
    };
}