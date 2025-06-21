#include "Metamorphic/pch.h"
#include "Core/Time.h"

namespace Metamorphic{
    float Time::s_TimeElapsed = 0;
    float Time::s_LastFrame = 0;
    float Time::s_DeltaTime = 0;

    std::chrono::high_resolution_clock Time::s_Clock;
    std::chrono::time_point<std::chrono::steady_clock> Time::s_LastFrameTimePoint;

    void Time::Init() noexcept{
        s_TimeElapsed = 0;
        s_LastFrame = 0;
        s_DeltaTime = 0;

        auto now = s_Clock.now();
        s_LastFrameTimePoint = now;
    }

    void Time::Update() noexcept{
        auto now = s_Clock.now();
        std::chrono::duration<float> deltaTime = now - s_LastFrameTimePoint;
        s_DeltaTime = deltaTime.count();
        s_TimeElapsed+=s_DeltaTime;
        s_LastFrameTimePoint = now;
    }
}