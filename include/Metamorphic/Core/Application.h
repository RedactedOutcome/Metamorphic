#pragma once

#include "Metamorphic/Rendering/IWindow.h"
#include "Metamorphic/Rendering/IRenderAPI.h"
#include "Metamorphic/SceneManagement/SceneManager.h"
#include "Metamorphic/Physics/IPhysicsAPI.h"

namespace Metamorphic{
    enum ApplicationError{
        None=0,
        FailedToCreateWindow,
        FailedToInitializeRenderer,
        FailedToInitializePhysics
    };
    class Application{
    public:
        Application()noexcept;
        ~Application()noexcept;
        
        ApplicationError Init()noexcept;
        void Update()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
        void Run()noexcept;
        void Shutdown()noexcept;
    public:
        /// @brief After program is initialized in the Run Method
        virtual void AfterInitialized()noexcept{}
        /// @brief Before shutting down the program in the Run Method, only called program was initially initialized correctly
        virtual void BeforeShutdown()noexcept{}
    public:
        EventDispatcher& GetEventDispatcher() const noexcept{return (EventDispatcher&)m_EventDispatcher;}
        IWindow* GetWindow() const noexcept{return m_Window.get();}
        IRenderAPI* GetRenderer() const noexcept{return m_Renderer.get();}
    #ifndef METAMORPHIC_NO_PHYSICS_ENGINE
        IPhysicsAPI* GetPhysicsAPI() const noexcept{return m_Physics.get();}
    #ifndef 
        SceneManager& GetSceneManager() const noexcept{return (SceneManager&)m_SceneManager;}
    protected:
        EventDispatcher m_EventDispatcher;
        std::unique_ptr<IWindow> m_Window;
        std::unique_ptr<IRenderAPI> m_Renderer;
    #ifndef METAMORPHIC_NO_PHYSICS_ENGINE
        std::unique_ptr<IPhysicsAPI> m_Physics;
    #endif
        SceneManager m_SceneManager;
    };

    extern Application* CreateApplication()noexcept;
}