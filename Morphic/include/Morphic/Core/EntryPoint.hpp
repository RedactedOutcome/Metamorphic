#pragma once

#include "Morphic.h"
using namespace Morphic;
int main(int argc, char** argv){
    Application* application = Application::CreateApplication();
    application->Run();
    delete application;
}