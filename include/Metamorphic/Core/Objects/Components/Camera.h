#pragma once

#include "../Component.h"

namespace Metamorphic{
    class Camera : public Component{
    public:
        Camera()noexcept;

        void Awake()noexcept override;
        void Start()noexcept override;
        void Update()noexcept override;
        void LateUpdate()noexcept override;
        void Update()noexcept override;
        void Draw()noexcept override;
        void LateDraw()noexcept override;
    };
}