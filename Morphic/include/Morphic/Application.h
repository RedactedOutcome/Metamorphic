#pragma once

#include "pch.h"
#include "Core.h"
#include "Scene/Scene.h"

namespace Morphic{
    extern class Application* CreateApplication();
    class MORPHIC_API Application{
    public:
        /// @brief Returns a singleton if instantiated
        /// @return 
        static Application* GetApplication() noexcept{return s_Application;}

        Application();
        ~Application();

        void Run();
        virtual void OnApplicationStarted();

    protected:
        std::vector<Scene*> m_Scenes;
    private:
        static Application* s_Application;

        //This function calls awake on all scenes
        void Awake();
        //This function calls start on all scenes
        void Start();
        /// @brief This function calls update on all scenes
        void Update();
        /// @brief This prepares the renderapi for drawing, draws scenes, clears depth buffer, then late draws
        void Draw();
        /// @brief this shutsdown all necessary core components of the engine such as physics, lighting, rendering, windows, gameobjects, ect
        void CleanUp();
        /// @brief calls scenes Onbefore exit so we can do stuff before program exits
        void OnBeforeExit();
    };
}