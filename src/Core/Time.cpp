#pragma once
#include "Core/Time.h"
#include <chrono>

namespace SuperEngine
{
    void Time::Tick()
    {
        if (isFirstFrame)
        {
            lastFrameTime = std::chrono::high_resolution_clock::now();
            isFirstFrame = false;
        }
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> _deltaTime = currentTime - lastFrameTime;

        deltaTime = _deltaTime.count();

        lastFrameTime = currentTime;
    }
}
