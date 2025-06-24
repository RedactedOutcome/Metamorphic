#pragma once

#include "Metamorphic/Core/Objects/GameObject.h"

namespace Metamorphic{
    enum class SceneBuildIndex{
        None=0,
        MainMenu
    };

    class SceneManager;
    /// @brief A default scene class
    class Scene{
    public:
        friend class SceneManager;
        Scene(SceneManager* manager) noexcept;
        virtual ~Scene() noexcept;

        /// @brief Call when scene is created/allocated.
        virtual void Awake()noexcept;
        /// @brief Call after scene is awoken
        virtual void Start()noexcept;
        /// @brief Called at the start of every frame
        virtual void Update()noexcept;
        /// @brief Called at the start of every frame
        virtual void FixedUpdate()noexcept;
        /// @brief Called after Fixed Update and physics calculations
        virtual void LateUpdate()noexcept;
        /// @brief Called after LateUpdate()
        virtual void Draw()noexcept;
        virtual void LateDraw()noexcept;
    public:
        GameObject* CreateGameObject() noexcept;
    public:
        void SetName(const HBuffer& name)noexcept{m_Name = name;}
        void SetName(HBuffer&& name)noexcept{m_Name = std::move(name);}
    public:
        SceneBuildIndex GetBuildIndex() const noexcept{return m_SceneIndex;}
        const HBuffer& GetName() const noexcept{return m_Name;}
        bool IsAwoken()const noexcept{return m_Awoken;}
        std::vector<std::unique_ptr<GameObject>>& GetGameObjects(){return (std::vector<std::unique_ptr<GameObject>>&)m_GameObjects;}
    private:
        SceneManager* m_SceneManager = nullptr;
        SceneBuildIndex m_SceneIndex = SceneBuildIndex::None;
        HBuffer m_Name = "Scene";
        bool m_Awoken = false;
        bool m_Started = false;
        std::vector<std::unique_ptr<GameObject>> m_GameObjects;
    };
}