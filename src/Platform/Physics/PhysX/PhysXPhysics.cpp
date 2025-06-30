#include "Metamorphic/pch.h"
#include "Platform/Physics/PhysX/PhysXPhysics.h"
#include "Core/Logger.h"

namespace Metamorphic{
    PhysXPhysics::PhysXPhysics()noexcept : IPhysicsAPI(), m_API(PhysicsAPI::PhysX){
        MORPHIC_DEBUG("Initializing PhysXPhysice");
    }
    PhysXPhysics::~PhysXPhysics()noexcept{}

    PhysicsAPIError PhysXPhysics::Init()noexcept{
        return PhysicsAPIError::None;
    }
    PhysicsAPIError PhysXPhysics::Shutdown()noexcept{
        return PhysicsAPIError::None;
    }

    void PhysXPhysics::Update()noexcept{

    }
}