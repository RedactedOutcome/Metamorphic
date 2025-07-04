#pragma once

#include "Metamorphic/Physics/IPhysicsAPI.h"

namespace Metamorphic{
    class METAMORPHIC_API PhysXPhysics : public IPhysicsAPI{
    public:
        PhysXPhysics()noexcept;
        ~PhysXPhysics()noexcept override;

        PhysicsAPIError Init()noexcept override;
        PhysicsAPIError Shutdown()noexcept override;

        void Update() noexcept override;
    };
}