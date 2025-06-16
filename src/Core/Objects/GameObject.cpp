#include "Metamorhpic/pch.h"
#include "Core/Objects/GameObject.h"

namespace Metamorphic{
    GameObject::GameObject()noexcept{}
    GameObject::~GameObject()noexcept{}

    void GameObject::Awake()noexcept{}
    void GameObject::Update()noexcept{}
    void GameObject::LateUpdate()noexcept{}
    void GameObject::Draw()noexcept{}
    void GameObject::LateDraw()noexcept{}
}