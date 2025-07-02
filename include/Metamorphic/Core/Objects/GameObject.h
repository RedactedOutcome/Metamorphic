#pragma once

#include "Transform.h"
#include "Component.h"
#include "Metamorphic/Core/Event/EventDispatcher.h"

namespace Metamorphic{
    class METAMORPHIC_API GameObject{
    public:
        GameObject()noexcept;
        ~GameObject()noexcept;

        void Awake()noexcept;
        void Start()noexcept;
        void Update()noexcept;
        void FixedUpdate()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
    public:
        template<typename T, typename... Args>
        std::unique_ptr<T>& CreateComponent(Args&&... args)noexcept{
            m_Components.emplace_back(std::make_unique<T>(std::forward<Args>(args)));
            return m_Components[m_Components.size() - 1];
        }
    public:
        bool IsEnabled()const noexcept{return m_Enabled;}
        EventDispatcher& GetEventDispatcher()const noexcept{return (EventDispatcher&)m_EventDispatcher;}
        Transform<METAMORPHIC_DEFAULT_VECTOR_TYPE, float>& GetTransform() const noexcept{return (Transform<METAMORPHIC_DEFAULT_VECTOR_TYPE, float>&)m_Transform;}
        std::vector<std::unique_ptr<Component>>& GetComponents() const noexcept{return (std::vector<std::unique_ptr<Component>>&)m_Components;}
    private:
        bool m_Enabled = true;
        EventDispatcher m_EventDispatcher;
        Transform<METAMORPHIC_DEFAULT_VECTOR_TYPE, float> m_Transform;
        std::vector<std::unique_ptr<Component>> m_Components;
    };
}