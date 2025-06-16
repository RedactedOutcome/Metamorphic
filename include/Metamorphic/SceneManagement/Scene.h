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

        /// @brief Call when scene is created/allocated.
        virtual void Awake()noexcept;
        /// @brief Call after scene is awoken
        virtual void Start()noexcept;

        virtual void Update()noexcept;
        /// @brief Called after Update
        virtual void LateUpdate()noexcept;
        /// @brief Called after LateUpdate()
        virtual void Draw()noexcept;
        virtual void LateDraw()noexcept;
    public:
        void SetName(const HBuffer& name)noexcept{m_Name = name;}
        void SetName(HBuffer&& name)noexcept{m_Name = std::move(name);}
    public:
        SceneBuildIndex GetBuildIndex() const noexcept{return m_SceneIndex;}
        const HBuffer& GetName() const noexcept{return m_Name;}
    private:
        SceneBuildIndex m_SceneIndex = SceneBuildIndex::None;
        HBuffer m_Name = "Scene";
    };
}