#include "Metamorphic.h"
#include "Metamorphic/EntryPoint.h"

using namespace Metamorphic;

class CustomScene : public Scene{
public:
    CustomScene(SceneManager* sceneManager)noexcept : Scene(sceneManager){
        GameObject* obj = CreateGameObject();
        for(size_t i = 0; i < 5; i++){
            CreateGameObject();
        }

        m_MeshData.SetBufferTypes(BufferType::Float, BufferType::UInt32);
    }
    ~CustomScene()noexcept{}

    void Draw()noexcept override{
        //SANDBOX_DEBUG("UPDATING");

    }
private:
    TexturedMeshData m_MeshData;
};
class SandboxApp : public Application{
public:
    SandboxApp()noexcept{
        m_ApplicationName = "SandboxApp";
    }
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