#include "Metamorphic/pch.h"
#include "Core/Application.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Core/Core.h"

/// TODO: check macros for platform specific window and renderer
#include "Platform/Window/WindowsWindow.h"
#include "Platform/Renderers/OpenGLRenderer.h"
#include "Platform/Renderers/VulkanRenderer.h"
#include "Platform/Physics/PhysX/PhysXPhysics.h"

namespace Metamorphic{
    Application::Application()noexcept{}
    Application::~Application()noexcept{}

    void Application::Run()noexcept{
        ApplicationError error = Init();
        if(error != ApplicationError::None){
            Shutdown();
            return;
        }
        AfterInitialized();
        while(m_Window->IsCreated()){
            Time::Update();
            Update();
            LateUpdate();
            //MORPHIC_INFO("FPS {0}", (1.0f / Time::GetDeltaTime()));
            Draw();
            LateDraw();
            m_Window->Update();
        }
        BeforeShutdown();
        Shutdown();
    }

    ApplicationError Application::Init()noexcept{
        Logger::Init();

        WindowProps props(1280, 720, m_ApplicationName);
        m_Window = std::make_unique<WindowsWindow>(std::move(props));
        WindowError error = m_Window->Create();
        if(error != WindowError::None){
            MORPHIC_ERROR("Failed to create window");
            return ApplicationError::FailedToCreateWindow;
        }
        m_Window->SetEventDispatcher(&m_EventDispatcher);
        m_Window->Show();
        MORPHIC_INFO("Created Window");

        m_Renderer = std::make_unique<VulkanRenderer>(m_Window.get());
        if(m_Renderer->Init() != RenderAPIError::None){
            MORPHIC_ERROR("Failed to initialize Renderer");
            return ApplicationError::FailedToInitializeRenderer;
        }
        MORPHIC_INFO("Initialized Renderer");

    #ifndef METAMORPHIC_NO_PHYSICS_ENGINE
        m_Physics = std::make_unique<PhysXPhysics>();
        if(m_Physics->Init() != PhysicsAPIError::None){
            MORPHIC_ERROR("Failed to initialize Physics");
            return ApplicationError::FailedToInitializePhysics;
        }
    #endif
        
        MORPHIC_INFO("Initialized");
        return ApplicationError::None;
    }

    void Application::Update()noexcept{
        m_SceneManager.Update();
    }
    void Application::FixedUpdate()noexcept{
        m_SceneManager.FixedUpdate();
    #ifndef METAMORPHIC_NO_PHYSICS_ENGINE
        m_Physics->Update();
    #endif
    }
    void Application::LateUpdate()noexcept{
        m_SceneManager.LateUpdate();
    }
    void Application::Draw()noexcept{
        m_Renderer->PrepareScreen();
        m_SceneManager.Draw();
    }
    void Application::LateDraw()noexcept{
        m_Renderer->ClearDepthBuffers();
        m_SceneManager.LateDraw();
        m_Renderer->Update();
    }

    void Application::Shutdown()noexcept{
        MORPHIC_INFO("Shutting Down");
        m_SceneManager.Shutdown();
    #ifndef METAMORPHIC_NO_PHYSICS_ENGINE
        if(m_Physics){
            m_Physics->Shutdown();
            m_Physics.reset();
        }
    #endif
        if(m_Renderer){
            m_Renderer->Shutdown();
            m_Renderer.reset();
        }
        if(m_Window){
            m_Window->Destroy();
            m_Window.reset();
        }
        MORPHIC_INFO("Shutdown");
    }
}