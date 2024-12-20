#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    class MORPHIC_API Scene{
    public:
        Scene();
        ~Scene();

        void Awake();
        void Start();
        void Update();
        void Draw();
        void LateDraw();

        void OnBeforeExit();
        void CleanUp();
    private:
    };
}