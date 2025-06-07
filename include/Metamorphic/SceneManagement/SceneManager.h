#pragma once

#include "Scene.h"

namespace Metamorphic{
    class SceneManager{
    public:
        void Init()noexcept;
        void Shutdown()noexcept;
    
        void Update()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
    
        /// @brief allocates a new scene of type SCENE. Calls the scenes Awake() and Start(). Then we add to the scene list
        template <typename SCENE, typename... Args>
        SCENE* AddScene(Args&&... args) noexcept{
            SCENE* scene = new SCENE(std::forward<Args>(args)...);
            scene->Awake();
            scene->Start();
            s_Scenes.emplace_back(static_cast<Scene*>(scene));
            return scene;
        }
    
        /// @brief Checks if the scene list contains param scene and if so we remove it. Note: we do not free scene
        bool RemoveScene(Scene* scene)noexcept;
        /// @brief Checks if the scene list contains param scene and if so we remove then free it.
        bool DeleteScene(Scene* scene)noexcept;

        /// @brief returns the first scene with the same buildIndex as param index. nullptr if not able to find one
        Scene* GetSceneByBuildIndex(SceneBuildIndex index)noexcept;
    private:
        std::vector<Scene*> s_Scenes;
    };
}