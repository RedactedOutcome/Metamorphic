#include "Metamorphic.h"
#include "Metamorphic/EntryPoint.h"

using namespace Metamorphic;

class CustomScene : public Scene{
public:
    CustomScene(SceneManager* sceneManager)noexcept : Scene(sceneManager){}
    ~CustomScene()noexcept{}

    void Update()noexcept override{
        //SANDBOX_DEBUG("UPDATING");
    }
};
class SandboxApp : public Application{
public:
    SandboxApp()noexcept{}
    ~SandboxApp()noexcept{}

    void AfterInitialized()noexcept override{
        SANDBOX_DEBUG("Initialized");

        //m_SceneManager.AddScene(Scene);
        Scene* scene = m_SceneManager.CreateScene<CustomScene>();
        scene->CreateGameObject();
    }

    void BeforeShutdown()noexcept override{
        SANDBOX_DEBUG("Shutting down");
    }
};
Application* Metamorphic::CreateApplication()noexcept{
    return new SandboxApp();
}