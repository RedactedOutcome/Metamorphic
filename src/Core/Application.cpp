#include "Core/Application.h"

#include "Platform/Window/WindowsWindow.h"
#include "Core/Logger.h"

namespace Metamorphic{
    Application::Application()noexcept{}
    Application::~Application()noexcept{}

    void Application::Run()noexcept{
        Logger::Init();

        m_Window = std::make_unique<WindowsWindow>();
        WindowError error = m_Window->Create();

        if(error != WindowError::None){
            MORPHIC_ERROR("Failed to create window");
        }
        MORPHIC_INFO("Created Window");

        MORPHIC_INFO("Initialized Application");
        while(m_Window->IsCreated()){
        }
        MORPHIC_INFO("Shutting Down");
        m_Window->Destroy();
        MORPHIC_INFO("Shutdown");
    }
}