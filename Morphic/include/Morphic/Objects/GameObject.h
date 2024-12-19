#pragma once

#include "Transform.h"
#include "Component.h"

namespace Morphic{
    class GameObject{
    public:
        GameObject();
        ~GameObject();
        
        Transform m_Transform;
    };
}