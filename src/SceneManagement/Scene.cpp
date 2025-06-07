#include "Metamorphic/pch.h"
#include "Metamorphic/SceneManagement/Scene.h"

namespace Metamorphic{
    Scene::Scene() noexcept{}
    Scene::~Scene() noexcept{}
    
    void Scene::Awake()noexcept{}
    void Scene::Start()noexcept{}
    void Scene::Update()noexcept{}
    void Scene::Draw()noexcept{}
    void Scene::LateDraw()noexcept{}
}