#pragma once

#include "Component.h"
namespace Metamorphic{
    class GameObject{
    public:
        GameObject()noexcept;
        ~GameObject()noexcept;

        void Awake()noexcept;
        void Update()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
    public:
        
    };
}