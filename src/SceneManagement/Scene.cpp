#include "Metamorphic/pch.h"
#include "Metamorphic/SceneManagement/Scene.h"

namespace Metamorphic{
    Scene::Scene(SceneManager* scene) noexcept : m_SceneManager(scene){}
    Scene::~Scene() noexcept{}

    void Scene::Awake()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->Awake();
    }
    void Scene::Start()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->Start();
    }
    void Scene::Update()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->Update();
    }
    void Scene::LateUpdate()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->LateUpdate();
    }
    void Scene::FixedUpdate()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->FixedUpdate();
    }
    void Scene::Draw()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->Draw();
    }
    void Scene::LateDraw()noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++)
            m_GameObjects[i]->LateDraw();
    }

    GameObject* Scene::CreateGameObject()noexcept{
        std::unique_ptr<GameObject> object = std::make_unique<GameObject>();
        GameObject* ptr = object.get();
        m_GameObjects.emplace_back(std::move(object));

        if(m_Awoken){
            ptr->Awake();
            ptr->Start();
        }
        return ptr;
    }

    void Scene::BroadcastEvent(Event& event)noexcept{
        for(size_t i = 0; i < m_GameObjects.size(); i++){
            m_GameObjects[i]->GetEventDispatcher();
        }
    }
}