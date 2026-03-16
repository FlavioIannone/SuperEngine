#pragma once
#include <iostream>
#include <atomic>
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include "Core/SceneManagement/Scene.h"

namespace SuperEngine
{
    class Engine
    {
    private:
        std::atomic<bool> isRunning = true;
        std::vector<std::unique_ptr<Scene>> m_scenes;
        Scene *m_activeScene = nullptr;
        SDL_Window *m_window = nullptr;
        SDL_Renderer *m_renderer = nullptr;

    public:
        // Constructor
        Engine();
        // Destructor
        ~Engine();

        // methods
        void Run();
        void Stop() { isRunning = false; }

        Scene *CreateScene(std::string);
        Scene *CreateScene();
        Scene *GetActiveScene() const { return m_activeScene; };
        void SetActiveScene(uint64_t sceneId);
    };
}