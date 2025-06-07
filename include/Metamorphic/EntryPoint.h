
int main(int argc, char** argv){
    using namespace Metamorphic;
    Application* application = CreateApplication();
    application->Run();
    delete application;
}