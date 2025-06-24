#pragma once

#include "Scene.h"

namespace Metamorphic{
    /// @brief A scene manager that handles scene classes. No use of smart
    class SceneManager{
    public:
        void Init()noexcept;
        void Shutdown()noexcept;
    
        void Update()noexcept;
        void FixedUpdate()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
    
        /// @brief allocates a new scene of type SCENE. Calls the scenes Awake() and Start(). Then we add to the scene list
        template <typename SCENE=Scene, typename... Args>
        SCENE* CreateScene(Args&&... args) noexcept{
            SCENE* scene = new SCENE(this, std::forward<Args>(args)...);
            m_Scenes.emplace_back(static_cast<Scene*>(scene));
            return scene;
        }

        /// @brief Checks if the scene list contains param scene and if so we remove it. Note: we do not free scene
        bool RemoveScene(Scene* scene)noexcept;
        /// @brief Checks if the scene list contains param scene and if so we remove then free it.
        bool DeleteScene(Scene* scene)noexcept;
    public:
        /// @brief returns the first scene with the same buildIndex as param index. nullptr if not able to find one
        Scene* GetSceneByBuildIndex(SceneBuildIndex index)noexcept;
        Scene* GetSceneByName(const HBuffer& sceneName)noexcept;
    private:
        std::vector<std::unique_ptr<Scene>> m_Scenes;
        std::vector<Scene*> m_ScenesToAwake;
        std::vector<Scene*> m_ScenesToStart;
    };
}