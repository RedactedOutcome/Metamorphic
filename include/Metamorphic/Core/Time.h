#pragma once

namespace Metamorphic{
    class Time{
    public:
        static void Init() noexcept;
        static void Update() noexcept;

        /// @brief the amount of time elapsed since the application started running at the start of the frame.
        static float GetTimeElapsed() noexcept{return s_TimeElapsed;}

        /// @brief the time the last frame had an update at
        static float GetLastFrame() noexcept{return s_LastFrame;}

        /// @brief the amount of time passed since the last frame update
        static float GetDeltaTime() noexcept{return s_DeltaTime;}
    private:
        static float s_TimeElapsed;
        static float s_LastFrame;
        static float s_CurrentFrame;
        static float s_DeltaTime;

        static std::chrono::high_resolution_clock s_Clock;
        static std::chrono::time_point<std::chrono::steady_clock> s_LastFrameTimePoint; 
    };
}