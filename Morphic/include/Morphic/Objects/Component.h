#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    class GameObject;
    class Component{
    public:
        GameObject()MORPHIC_NOEXCEPT;
        ~GameObject();
        const GameObject* GetGameObject()MORPHIC_NOEXCEPT{return m_GameObject;}
    private:
        /// @brief The gameobject the component is attached to
        GameObject* m_GameObject;
    };
}