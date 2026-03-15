#include "Core/Time.h"
#include <chrono>

namespace SuperEngine
{
    void Time::Tick()
    {
        using namespace std::chrono;
        time_point<high_resolution_clock> currentTime = high_resolution_clock::now();

        if (isFirstFrame)
        {
            startTime = currentTime;
            lastFrameTime = currentTime;
            isFirstFrame = false;
            return;
        }

        duration<float> deltaTime = currentTime - lastFrameTime;
        m_deltaTime = deltaTime.count();
        lastFrameTime = currentTime;

        duration<float> totalTime = currentTime - startTime;
        m_totalTime = totalTime.count();
    }
}
