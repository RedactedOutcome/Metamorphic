#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core.h"

namespace Metamorphic{
    /// @brief A debug class that times the amount of time before a scope ends.
    class METAMORPHIC_API Stopwatch{
    public:
        ScopedTimer()noexcept;
        ~ScopedTimer()noexcept;

        void Stop()noexcept;
        /// TODO: have ostream operator
    public:
        float GetTimeElapsed()const noexcept;
    private:
        std::chrono::high_resolution_clock Time::s_Clock;
        std::chrono::time_point<std::chrono::steady_clock> Time::s_LastFrameTimePoint;
    };
}