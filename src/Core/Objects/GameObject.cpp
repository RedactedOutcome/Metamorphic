#include "Metamorphic/pch.h"
#include "Core/Objects/GameObject.h"

namespace Metamorphic{
    GameObject::GameObject()noexcept{}
    GameObject::~GameObject()noexcept{}

    void GameObject::Awake()noexcept{
        for(size_t i = 0; i < m_Components.size(); i++){
            m_Components[i]->Awake();
        }
    }
    void GameObject::Start()noexcept{
        for(size_t i = 0; i < m_Components.size(); i++){
            m_Components[i]->Start();
        }
    }
    void GameObject::Update()noexcept{
        m_Transform.Update();
        for(size_t i = 0; i < m_Components.size(); i++){
            m_Components[i]->Update();
        }
    }
    void GameObject::LateUpdate()noexcept{
        for(size_t i = 0; i < m_Components.size(); i++){
            m_Components[i]->LateUpdate();
        }
    }
    void GameObject::Draw()noexcept{
        for(size_t i = 0; i < m_Components.size(); i++){
            m_Components[i]->Draw();
        }
    }
    void GameObject::LateDraw()noexcept{
        for(size_t i = 0; i < m_Components.size(); i++){
            m_Components[i]->LateDraw();
        }
    }
}