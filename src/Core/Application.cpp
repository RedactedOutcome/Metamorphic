#include "Metamorphic/pch.h"
#include "Core/Application.h"
#include "Core/Time.h"
#include "Core/Logger.h"

/// TODO: check macros for platform specific window and renderer
#include "Platform/Window/WindowsWindow.h"
#include "Platform/Renderers/OpenGLRenderer.h"

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

        WindowProps props(1280, 720, "Hello World");
        m_Window = std::make_unique<WindowsWindow>(std::move(props));
        WindowError error = m_Window->Create();
        if(error != WindowError::None){
            MORPHIC_ERROR("Failed to create window");
            return ApplicationError::FailedToCreateWindow;
        }
        m_Window->Show();
        MORPHIC_INFO("Created Window");

        m_Renderer = std::make_unique<OpenGLRenderer>(m_Window.get());
        if(m_Renderer->Init() != RenderAPIError::None){
            MORPHIC_ERROR("Failed to initialize Renderer");
            return ApplicationError::FailedToInitializeRenderer;
        }
        MORPHIC_INFO("Initialized Renderer");

        MORPHIC_INFO("Initialized");
        return ApplicationError::None;
    }

    void Application::Update()noexcept{
        m_SceneManager.Update();
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
    }

    void Application::Shutdown()noexcept{
        MORPHIC_INFO("Shutting Down");
        m_SceneManager.Shutdown();

        if(m_Window){
            m_Window->Destroy();
            m_Window.reset();
        }
        MORPHIC_INFO("Shutdown");
    }
}