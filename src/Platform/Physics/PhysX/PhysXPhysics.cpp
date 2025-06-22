#include "Metamorphic/pch.h"
#include "Platform/Physics/PhysX/PhysXPhysics.h"

namespace Metamorphic{
    PhysXPhysics::PhysXPhysics()noexcept : IPhysicsAPI(){}
    PhysXPhysics::~PhysXPhysics()noexcept{}

    PhysicsAPIError PhysXPhysics::Init()noexcept{}
    PhysicsAPIError PhysXPhysics::Shutdown()noexcept{}
}