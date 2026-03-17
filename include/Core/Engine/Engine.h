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
        // Flags
        std::atomic<bool> isRunning = true;
        // Scene Management
        std::vector<std::unique_ptr<Scene>> m_scenes;
        Scene *m_activeScene = nullptr;

        // SDL window and renderer
        SDL_Window *m_window = nullptr;
        SDL_Renderer *m_renderer = nullptr;

        // Values
        int width;
        int height;
        int fov;

    public:
        // Singleton methods
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        static Engine &GetInstance()
        {
            static Engine instance;
            return instance;
        }

        // methods
        void Run();
        void Stop() { isRunning = false; }

        // Scene Management
        Scene *CreateScene(std::string);
        Scene *CreateScene();
        Scene *GetActiveScene() const { return m_activeScene; };
        void SetActiveScene(uint64_t sceneId);

        // Setters
        void SetWidth(int width) { Engine::width = width; }
        void SetHeight(int height) { Engine::height = height; }
        void SetFieldOfView(int fieldOfView) { Engine::fov = fieldOfView; }
        // Getters
        int GetWidth() { return width; }
        int GetHeight() { return height; }
        int GetFieldOfView() { return fov; }

    private:
        Engine();
        ~Engine();
    };
}