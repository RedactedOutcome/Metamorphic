#include "Metamorphic.h"
#include "Metamorphic/EntryPoint.h"
#include <iostream>

using namespace Metamorphic;

class SandboxApp : public Application{
public:
    SandboxApp()noexcept{
        std::cout << "Hello SandboxAPp"<<std::endl;
    }
    ~SandboxApp()noexcept{
        std::cout << "Bye SandboxApp"<<std::endl;
    }
};
Application* Metamorphic::CreateApplication()noexcept{
    return new SandboxApp();
}