/// @brief This file is not included in the engine build process. This file stands as a
/// Simple main function that simple starts and executes the Metamorphic Engine and project 
int main(int argc, char** argv){
    using namespace Metamorphic;
    std::unique_ptr<Application> application(CreateApplication());
    application->Run();
}