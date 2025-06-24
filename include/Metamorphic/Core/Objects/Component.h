#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Event/EventDispatcher.h"

namespace Metamorphic{
    class GameObject;
    class Component{
    public:
        Component(GameObject* gameObject)noexcept;
        ~Component()noexcept;

    public:
        virtual void Awake()noexcept=0;
        virtual void Start()noexcept=0;
        virtual void Update()noexcept=0;
        virtual void FixedUpdate()noexcept=0;
        virtual void LateUpdate()noexcept=0;
        virtual void Draw()noexcept=0;
        virtual void LateDraw()noexcept=0;
    public:
        bool IsEnabled() const noexcept{return m_Enabled;}
        GameObject* GetGameObject()const noexcept{return m_GameObject;}
        EventDispatcher& GetEventDispatcher() const noexcept{return (EventDispatcher&)m_EventDispatcher;}
    private:
        bool m_Enabled = true;
        GameObject* m_GameObject = nullptr;
        EventDispatcher m_EventDispatcher;
    };
}