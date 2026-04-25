#include "SuperEngine/Time.h"
#include "SuperEngine/Engine/Engine.h"
#include <chrono>

namespace SuperEngine
{
    void Time::Tick()
    {
        using namespace std::chrono;
        time_point<high_resolution_clock> currentTime = high_resolution_clock::now();
        static bool isFirstTick = true;

        if (isFirstTick)
        {
            isFirstTick = false;
            startTime = currentTime;
            lastFrameTime = currentTime;
            m_deltaTime = 0.0f;
            m_totalTime = 0.0f;
            return;
        }

        duration<float> deltaTime = currentTime - lastFrameTime;
        m_deltaTime = deltaTime.count();
        lastFrameTime = currentTime;

        duration<float> totalTime = currentTime - startTime;
        m_totalTime = totalTime.count();
    }
}
