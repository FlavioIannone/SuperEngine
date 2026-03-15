#pragma once
#include <iostream>
#include <atomic>
#include <vector>
#include <string>
#include <memory>
#include "Core/SceneManagement/Scene.h"

namespace SuperEngine
{
    class Engine
    {
    private:
        std::atomic<bool> isRunning = true;
        std::vector<std::unique_ptr<Scene>> m_scenes;
        Scene *m_activeScene = nullptr;

    public:
        // Constructor
        Engine() { std::cout << "Engine started.\n"; }
        // Destructor
        ~Engine() { std::cout << "Engine terminated.\n"; }

        // methods
        void Run();
        void Stop() { isRunning = false; }

        Scene *CreateScene(std::string);
        Scene *CreateScene();
        Scene *GetActiveScene() const { return m_activeScene; };
        void SetActiveScene(uint64_t sceneId);
    };
}