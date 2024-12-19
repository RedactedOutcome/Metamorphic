#include <Morphic/Morphic.h>

#include <Morphic/Core/EntryPoint.hpp>

class SandboxApplication : Morphic::Application{
public:
    SandboxApplication(){}
    ~SandboxApplication(){}

    void OnApplicationStarted() override{
        
    }

};
Morphic::Application* Morphic::Application::CreateApplication(){
    return new SandboxApplication();
}