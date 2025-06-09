#include "Core/Application.h"

#include "Platform/Window/WindowsWindow.h"
#include "Core/Logger.h"

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
            Update();
            LateUpdate();
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
        m_SceneManager.Draw();
    }
    void Application::LateDraw()noexcept{
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