#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Objects/Component.h"
#include "Metamorphic/Core/Objects/GameObject.h"

namespace Metamorphic{
    Component::Component(GameObject* gameObject)noexcept : m_GameObject(gameObject){}
    Component::~Component()noexcept{}

    void Component::Awake()noexcept{}
    void Component::Start()noexcept{}
    void Component::Update()noexcept{}
    void Component::LateUpdate()noexcept{}
    void Component::Draw()noexcept{}
    void Component::LateDraw()noexcept{}
}