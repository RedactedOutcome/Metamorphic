#include "Metamorphic.h"
#include "Metamorphic/EntryPoint.h"
#include <iostream>

using namespace Metamorphic;

class SandboxApp : public Application{
public:
    SandboxApp()noexcept{}
    ~SandboxApp()noexcept{}

    void AfterInitialized()noexcept override{
        SANDBOX_DEBUG("Initialized");

        //m_SceneManager.AddScene(Scene);
        Scene* scene = m_SceneManager.CreateScene();
        scene->AddGameObject();
    }

    void BeforeShutdown()noexcept override{
        SANDBOX_DEBUG("Shutting down");
    }
};
Application* Metamorphic::CreateApplication()noexcept{
    return new SandboxApp();
}