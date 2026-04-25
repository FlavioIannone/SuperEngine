#pragma once
#include <iostream>
#include <atomic>
#include <vector>
#include <string>
#include <xstring>
#include <memory>
#include <SDL.h>
#include "SuperEngine/SceneManagement/Scene.h"
#include "SuperEngine/Graphics/GraphicsDevice.h"
#include "SuperEngine/Graphics/BuiltInShaders.h"

namespace SuperEngine
{
    class Engine
    {
    private:
        // Flags
        std::atomic<bool> isRunning = true;
        std::atomic<bool> isFirstFrame = true;
        std::atomic<bool> isVSyncActive = false;
        // Scene Management
        std::vector<std::unique_ptr<Scene>> m_scenes;
        Scene *m_activeScene = nullptr;

        // SDL window
        SDL_Window *m_window = nullptr;
        // Graphics objects
        std::unique_ptr<GraphicsDevice> graphicsDevice;
        std::unique_ptr<BuiltInShaders> builtInShaders;

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
        bool Init(int width, int height, bool isVSyncActive = true);
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
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        int GetFieldOfView() const { return fov; }
        bool IsFirstFrame() const { return isFirstFrame; }
        bool GetIsVSyncActive() const { return isVSyncActive; }
        GraphicsDevice *GetGraphicsDevice() const { return graphicsDevice.get(); }
        BuiltInShaders *GetBuiltInShaders() const { return builtInShaders.get(); }

    private:
        Engine() = default;
        ~Engine();

        // Internal methods
        void HandleSDLWindowEventPolling();
        bool InitSDLWindowAndGPUDevice();
    };
}