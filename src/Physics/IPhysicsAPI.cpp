#include "Metamorphic/pch.h"
#include "Physics/IPhysicsAPI.h"

namespace Metamorphic{
    IPhysicsAPI::IPhysicsAPI()noexcept{}
    IPhysicsAPI::~IPhysicsAPI()noexcept{}

    PhysicsAPIError IPhysicsAPI::Init()noexcept{}
    PhysicsAPIError IPhysicsAPI::Shutdown()noexcept{}
}