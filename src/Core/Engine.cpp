#include "Core/Engine.h"
#include "Core/Time.h"

namespace SuperEngine
{
    void Engine::Run()
    {
        while (isRunning)
        {
            Time::GetInstance().Tick();
        }
    }
}