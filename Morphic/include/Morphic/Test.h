#pragma once

#ifdef MORPHIC_EXPORTS
#pragma message("EXPORTING")
#define MORPHIC_API __declspec(dllexport)
#else
#pragma message(" IMPORTING")
#define MORPHIC_API __declspec(dllimport)
#endif

extern "C" class MORPHIC_API Test{
public:
    void SayHelloWorld();
};