#include "Morphic/pch.h"
#include "Morphic/Application.h"

namespace Morphic{
    Application* Application::s_Application = nullptr;

    Application::Application(){
        if(s_Application){
            std::exit(-1);
        }
        s_Application = this;
    }
    Application::~Application(){}

    void Application::Run(){
        OnApplicationStarted();
        Awake();
        Start();
        
        while(true){
            Update();
            Draw();
        }
        OnBeforeExit();
        CleanUp();
    }

    void Application::Awake(){
        for(size_t i = 0; i < m_Scenes.size(); i++){
            m_Scenes[i]->Awake();
        }
    }

    void Application::Start(){
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->Start();
    }
    
    void Application::Update(){
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->Update();
    }

    void Application::Draw(){
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->Draw();
        //TODO: Clear depth buffer
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->LateDraw();
    }

    void Application::OnBeforeExit(){
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->OnBeforeExit();
    }
    void Application::CleanUp(){
        for(size_t i = 0; i < m_Scenes.size(); i++)
            m_Scenes[i]->CleanUp();
    }
}