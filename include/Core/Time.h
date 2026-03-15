#pragma once
#include <chrono>

namespace SuperEngine
{
    class Time
    {
    private:
        std::chrono::high_resolution_clock::time_point lastFrameTime;
        std::chrono::high_resolution_clock::time_point startTime;
        double m_deltaTime = 0;
        double m_totalTime = 0;
        bool isFirstFrame = true;

        Time(const Time &) = delete;
        Time &operator=(const Time &) = delete;

    public:
        double GetDeltaTime() { return m_deltaTime; }
        double GetTotalTime() { return m_totalTime; }
        void Tick();
        static Time &GetInstance()
        {
            static Time instance;
            return instance;
        }

    private:
        Time() = default;
        ~Time() = default;
    };
}