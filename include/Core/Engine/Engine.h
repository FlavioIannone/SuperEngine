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
        std::atomic<bool> isFirstFrame = true;
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
        void SetWidth(int width)
        {
            Engine::width = width;
            if (m_window)
            {
                SDL_SetWindowSize(m_window, width, height);
                SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            }
            else
            {
                std::cout << "[Warning] The window is not initialized!\n";
            }
        }
        void SetHeight(int height)
        {
            Engine::height = height;
            if (m_window)
            {
                SDL_SetWindowSize(m_window, width, height);
                SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            }
            else
            {
                std::cout << "[Warning] The window is not initialized!\n";
            }
        }
        void SetFieldOfView(int fieldOfView) { Engine::fov = fieldOfView; }
        // Getters
        int GetWidth() { return width; }
        int GetHeight() { return height; }
        int GetFieldOfView() { return fov; }
        bool IsFirstFrame() { return isFirstFrame; }
        SDL_Renderer *GetRenderer() { return m_renderer; }

    private:
        Engine();
        ~Engine();

        // Internal methods
        void HandleSDLWindowEventPolling();
        bool InitSDLWindowAndRenderer();
    };
}