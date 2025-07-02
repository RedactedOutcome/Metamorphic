#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core.h"

namespace Metamorphic{
    class Timer METAMORPHIC_API{
    public:
        void Stop()noexcept;

    private:
        float m_TimeElapsed = 0;
    };
}