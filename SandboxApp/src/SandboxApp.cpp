#include <Morphic/Morphic.h>

#include <Morphic/Core/EntryPoint.hpp>

class SandboxApplication : Morphic::Application{
public:
    SandboxApplication();
    virtual SandboxApplication();
};
Morphic::Application* Morphic::Application::CreateApplication(){
    return new 
}