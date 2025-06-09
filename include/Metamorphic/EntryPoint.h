
int main(int argc, char** argv){
    using namespace Metamorphic;
    std::unique_ptr<Application> application(CreateApplication());
    application->Run();
}