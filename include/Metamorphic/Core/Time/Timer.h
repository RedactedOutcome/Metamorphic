#pragma once

#include "Metamorphic/pch.h"

namespace Metamorphic{
    class Timer{
    public:
        void Stop()noexcept;

    private:
        float m_TimeElapsed = 0;
    };
}