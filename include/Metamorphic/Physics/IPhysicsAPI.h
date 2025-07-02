#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    enum class PhysicsAPI{
        None=0,
        PhysX
    };

    enum class PhysicsAPIError{
        None=0
    };
    class METAMORPHIC_API IPhysicsAPI{
    public:
        IPhysicsAPI()noexcept;
        virtual ~IPhysicsAPI()noexcept;

        virtual PhysicsAPIError Init()noexcept=0;
        virtual PhysicsAPIError Shutdown()noexcept=0;

        virtual void Update()noexcept=0;
    protected:
        PhysicsAPI m_API = PhysicsAPI::None;
    };
}