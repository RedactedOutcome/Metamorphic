/// @brief This file is not included in the engine build process. This file stands as a
/// Simple main function that simple starts and executes the Metamorphic Engine and project 

#ifdef METAMORPHIC_PLATFORM_WINDOWS
int main(int argc, char** argv){
#else
#error Metamorphic No Supported Entry Point for this platform
#endif
    using namespace Metamorphic;
    std::unique_ptr<Application> application(CreateApplication());
    application->Run();
}