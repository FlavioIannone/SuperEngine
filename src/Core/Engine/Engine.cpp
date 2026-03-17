#include "Core/Engine/Engine.h"
#include "Core/Time.h"
#include "Core/IDManager.h"
#include <string>
#include <iostream>

namespace SuperEngine
{
    Engine::Engine()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "Error while initializing SDL: " << SDL_GetError() << "\n";
            system("pause");
            return;
        }

        // Window
        m_window = SDL_CreateWindow("SuperEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
        if (!m_window)
        {
            std::cout << "Error creating window: " << SDL_GetError() << std::endl;
            system("pause");
            return;
        }

        // Renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if (!m_renderer)
        {
            std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
            system("pause");
            return;
        }
        std::cout << "Engine started.\n";
    }
    Engine::~Engine()
    {
        if (m_renderer)
            SDL_DestroyRenderer(m_renderer);
        if (m_window)
            SDL_DestroyWindow(m_window);
        SDL_Quit();

        std::cout << "Engine terminated.\n";
    }
    void Engine::Run()
    {
        SDL_Event event;
        while (isRunning)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    isRunning = false;
                }
            }
            Time::GetInstance().Tick();
            if (m_activeScene != nullptr && m_activeScene->IsEnabled())
            {
                m_activeScene->Update();
            }

            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);

            // Draw phase

            SDL_RenderPresent(m_renderer);
        }
    }
    Scene *Engine::CreateScene(std::string name)
    {
        uint64_t id = IDManager<Scene>::GetNext();

        auto newScene = std::make_unique<Scene>(id, name);
        Scene *ptr = newScene.get();
        m_activeScene = ptr;
        m_scenes.push_back(std::move(newScene));
        return ptr;
    }
    Scene *Engine::CreateScene()
    {
        uint64_t id = IDManager<Scene>::GetNext();
        auto newScene = std::make_unique<Scene>(id, "Scene" + std::to_string(id));
        Scene *ptr = newScene.get();
        m_activeScene = ptr;
        m_scenes.push_back(std::move(newScene));
        return ptr;
    }
    void Engine::SetActiveScene(uint64_t sceneId)
    {
        for (auto &s : m_scenes)
        {
            if (s->GetId() == sceneId)
            {
                m_activeScene = s.get();
                return;
            }
        }

        std::cout << "[Warning] Scene with ID " << sceneId << " not found!\n";
    }
}