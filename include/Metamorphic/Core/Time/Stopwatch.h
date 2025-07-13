#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    /// @brief A debug class that times the amount of time before a scope ends.
    class METAMORPHIC_API Stopwatch{
    public:
        Stopwatch()noexcept;
        ~Stopwatch()noexcept;

        void Stop()noexcept;
        /// TODO: have ostream operator
    public:
        float GetTimeElapsed()const noexcept;
    private:
        std::chrono::high_resolution_clock s_Clock;
        std::chrono::time_point<std::chrono::steady_clock> s_LastFrameTimePoint;
    };
}