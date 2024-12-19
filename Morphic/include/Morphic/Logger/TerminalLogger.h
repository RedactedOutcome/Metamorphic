#pragma once

#include "Morphic/Core.h"

namespace Morphic{
    class MORPHIC_API TerminalLogger{
        static void Init(const char* loggerName);
        static void Shutdown();
    private:
    
    };
}