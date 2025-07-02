#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core.h"

namespace Metamorphic{
    class METAMORPHIC_API Timer{
    public:
        void Stop()noexcept;

    private:
        float m_TimeElapsed = 0;
    };
}