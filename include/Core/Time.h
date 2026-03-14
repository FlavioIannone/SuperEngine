#pragma once
#include <chrono>

namespace SuperEngine
{
    class Time
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
        float deltaTime = 0;
        bool isFirstFrame = true;

        Time(const Time &) = delete;
        Time &operator=(const Time &) = delete;

    public:
        inline float GetDeltaTime() { return deltaTime; }
        void Tick();
        inline static Time &GetInstance()
        {
            static Time instance;
            return instance;
        }

    private:
        Time() = default;
        ~Time() = default;
    };
}