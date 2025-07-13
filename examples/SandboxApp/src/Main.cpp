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

        m_MeshData.SetBufferDataTypes(BufferDataType::Float, BufferDataType::UInt32);
        m_Mesh.SetMeshData(&m_MeshData);

        m_Shader = m_SceneManager->GetApplication()->GetRenderer()->CreateShader();

        HBuffer vertexShaderData;
        HBuffer fragmentShaderData;

        ResourceManagerError error = ResourceManager::LoadResource(ResourceType::Shader, "res/shaders/test-vert", vertexShaderData);
        if(error != ResourceManagerError::None){
            APPLICATION_ERROR("Failed to load resource test-vert. Error {0}", (int)error);
            m_SceneManager->GetApplication()->Exit();
        }
        error = ResourceManager::LoadResource(ResourceType::Shader, "res/shaders/test-frag", fragmentShaderData);
        if(error != ResourceManagerError::None){
            APPLICATION_ERROR("Failed to load resource test-frag. Error {0}", (int)error);
            m_SceneManager->GetApplication()->Exit();
        }
        m_ShaderData.SetVertexShaderData(std::move(vertexShaderData));
        m_ShaderData.SetFragmentShaderData(std::move(fragmentShaderData));
        m_Shader->SetShaderData(&m_ShaderData);
    }
    ~CustomScene()noexcept{}

    void Draw()noexcept override{
        //APPLICATIONDEBUG("UPDATING");

    }
private:
    MeshData m_MeshData;
    BasicMesh m_Mesh;
    ShaderData m_ShaderData;
    std::unique_ptr<Shader> m_Shader;
};
class SandboxApp : public Application{
public:
    SandboxApp()noexcept{
        m_ApplicationName = "SandboxApp";
    }
    ~SandboxApp()noexcept{}

    void AfterInitialized()noexcept override{
        APPLICATION_DEBUG("Initialized");
        
        //m_SceneManager.AddScene(Scene);
        Scene* scene = m_SceneManager.CreateScene<CustomScene>();
        scene->CreateGameObject();
    }

    void BeforeShutdown()noexcept override{
        APPLICATION_DEBUG("Shutting down");
    }
};
Application* Metamorphic::CreateApplication()noexcept{
    return new SandboxApp();
}