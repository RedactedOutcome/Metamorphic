#include "Metamorphic/pch.h"
#include "Metamorphic/SceneManagement/SceneManager.h"

namespace Metamorphic{
    void SceneManager::Init()noexcept{
        s_Scenes.clear();
        s_Scenes.reserve(5);
    }
    void SceneManager::Shutdown()noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            delete s_Scenes[i];
        }
        s_Scenes.clear();
    }
    void SceneManager::Update()noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++)
            s_Scenes[i]->Update();
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
            if(s_Scenes[i] == scene){
                s_Scenes.erase(s_Scenes.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool SceneManager::DeleteScene(Scene* scene)noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            if(s_Scenes[i] == scene){
                s_Scenes.erase(s_Scenes.begin() + i);
                delete scene;
                return true;
            }
        }
        return false;
    }
    Scene* SceneManager::GetSceneByBuildIndex(SceneBuildIndex index)noexcept{
        for(size_t i = 0; i < s_Scenes.size(); i++){
            Scene* scene = s_Scenes[i];
            if(scene->GetBuildIndex() == index)return scene;
        }
        return nullptr;
    }
}