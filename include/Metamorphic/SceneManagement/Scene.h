#pragma once
#include "Metamorphic/pch.h"

namespace Metamorphic{
    enum class SceneBuildIndex{
        None=0,
        MainMenu
    };


    /// @brief A default scene class
    class Scene{
    public:
        Scene() noexcept;
        virtual ~Scene() noexcept;

        /// @brief Call when scene is allocated
        virtual void Awake()noexcept;
        /// @brief Call after scene is awoken
        virtual void Start()noexcept;

        virtual void Update()noexcept;
        virtual void Draw()noexcept;
        virtual void LateDraw()noexcept;
    public:
        SceneBuildIndex GetBuildIndex() const noexcept{return m_SceneIndex;}
    private:
        SceneBuildIndex m_SceneIndex = SceneBuildIndex::None;
    };
}