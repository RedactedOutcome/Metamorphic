#include <Morphic/Morphic.h>

#include <Morphic/Core/EntryPoint.hpp>

class SandboxApplication : public Morphic::Application{
public:
    SandboxApplication(){}
    ~SandboxApplication(){}

    void OnApplicationStarted() override{
    }

};
Morphic::Application* Morphic::CreateApplication(){
    return new SandboxApplication();
}