#pragma once

#include "Morphic/Morphic.h"

void signalHandler(int signal) {
    if (signal == SIGSEGV) {
        std::cout << "SIGSEGV received! Shutting down gracefully...\n";
    }
        std::cout << "Shutting down gracefully...\n";
    std::exit(-1);
}

using namespace Morphic;
int main(int argc, char** argv){
    std::signal(SIGSEGV, signalHandler);
    char b[2];
    b[15] = 0;
    Application* application = Morphic::CreateApplication();
    application->Run();
    delete application;
}