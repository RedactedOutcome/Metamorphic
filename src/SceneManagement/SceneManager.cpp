#include "Metamorphic/pch.h"
#include "Metamorphic/SceneManagement/SceneManager.h"

namespace Metamorphic{
    void SceneManager::Init()noexcept{
        m_Scenes.clear();
        m_Scenes.reserve(5);
    }
    void SceneManager::Shutdown()noexcept{
        m_Scenes.clear();
    }
    void SceneManager::Update()noexcept{
        for(size_t i = 0; i < m_ScenesToAwake.size(); i++){
            m_ScenesToAwake[i]->Awake();
            m_ScenesToStart.emplace_back(m_ScenesToStart[i]);
        }
        for(size_t i = 0; i < m_ScenesToStart.size(); i++)
            m_ScenesToStart[i]->Start();

        m_ScenesToAwake.clear();
        m_ScenesToStart.clear();
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->Update();
    }
    void SceneManager::LateUpdate()noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->LateUpdate();
    }
    void SceneManager::Draw()noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->Draw();
    }

    void SceneManager::LateDraw()noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->LateDraw();
    }
    bool SceneManager::RemoveScene(Scene* scene)noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++){
            if(m_Scenes[i].get() == scene){
                m_Scenes.erase(m_Scenes.begin() + i);

                /// Check scenes in awake/start list
                for(size_t j = 0; j < m_ScenesToAwake.size(); j++){
                    if(m_ScenesToAwake[j] == scene){
                        m_ScenesToAwake.erase(m_ScenesToAwake.begin() + j);
                        break;
                    }
                }
                for(size_t j = 0; j < m_ScenesToStart.size(); j++){
                    if(m_ScenesToStart[j] == scene){
                        m_ScenesToStart.erase(m_ScenesToStart.begin() + j);
                        break;
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool SceneManager::DeleteScene(Scene* scene)noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++){
            if(m_Scenes[i].get() == scene){
                m_Scenes.erase(m_Scenes.begin() + i);
                delete scene;
                return true;
            }
        }
        return false;
    }
    Scene* SceneManager::GetSceneByBuildIndex(SceneBuildIndex index)noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++){
            std::unique_ptr<Scene>& scene = m_Scenes[i];
            if(scene->GetBuildIndex() == index)return scene.get();
        }
        return nullptr;
    }

    Scene* SceneManager::GetSceneByName(const HBuffer& sceneName)noexcept{
        for(size_t i = 0; i < m_Scenes.size(); i++){
            std::unique_ptr<Scene>& scene = m_Scenes[i];
            if(scene->GetName() == sceneName)return scene.get();
        }

        return nullptr;
    }
}