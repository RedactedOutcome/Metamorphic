#include "Metamorphic/pch.h"
#include "Metamorphic/SceneManagement/SceneManager.h"

namespace Metamorphic{
    void SceneManager::Init()noexcept{
        s_Scenes.clear();
        s_Scenes.reserve(5);
    }
    void SceneManager::Shutdown()noexcept{
        s_Scenes.clear();
    }
    void SceneManager::Update()noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++)
            s_Scenes[i]->Update();
    }
    void SceneManager::LateUpdate()noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++)
            s_Scenes[i]->LateUpdate();
    }
    void SceneManager::Draw()noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++)
            s_Scenes[i]->Draw();
    }

    void SceneManager::LateDraw()noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++)
            s_Scenes[i]->LateDraw();
    }
    bool SceneManager::RemoveScene(Scene* scene)noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            if(s_Scenes[i].get() == scene){
                s_Scenes.erase(s_Scenes.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool SceneManager::DeleteScene(Scene* scene)noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            if(s_Scenes[i].get() == scene){
                s_Scenes.erase(s_Scenes.begin() + i);
                delete scene;
                return true;
            }
        }
        return false;
    }
    Scene* SceneManager::GetSceneByBuildIndex(SceneBuildIndex index)noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            std::unique_ptr<Scene>& scene = s_Scenes[i];
            if(scene->GetBuildIndex() == index)return scene.get();
        }
        return nullptr;
    }

    Scene* SceneManager::GetSceneByName(const HBuffer& sceneName)noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            std::unique_ptr<Scene>& scene = s_Scenes[i];
            if(scene->GetName() == sceneName)return scene.get();
        }

        return nullptr;
    }
}