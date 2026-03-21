#include "Core/Engine/Engine.h"
#include "Core/Time.h"
#include "Core/IDManager.h"
#include <string>
#include <iostream>
#include "Core/Engine/RenderingManager.h"

namespace SuperEngine
{
    Engine::Engine()
    {
        // This is the first frame
        isFirstFrame = true;
        if (!InitSDLWindowAndRenderer())
        {
            return;
        }

        std::cout << "Engine started.\n";
    }

    void Engine::Run()
    {
        isFirstFrame = false;
        // Call awake for the scenes.
        {
            scene->Awake();
        }
        // Call start for the scenes.
        for (auto &scene : m_scenes)
        {
            if (scene->IsEnabled())
            {
                scene->Start();
            }
        }
        while (isRunning)
        {
            Time::GetInstance().Tick();
            HandleSDLWindowEventPolling();
            // Calling update for each scene.
            if (m_activeScene != nullptr && m_activeScene->IsEnabled())
            {
                m_activeScene->Update();
            }
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);

            // Draw phase

            SDL_RenderPresent(m_renderer);
            // Do the cleanup for the scene, if a gameobject is pending a destroy, destroy if at the end of the frame
            if (m_activeScene != nullptr)
            {
                m_activeScene->Cleanup();
            }
        }
        // We perform logical cleanup here rather than in ~Engine() to prevent order-of-destruction bugs.
        // This guarantees that all subsystems (like RenderingManager) are still fully alive
        // when Components call their OnDestroy() methods to unregister themselves.
        for (auto &scene : m_scenes)
        {
            scene->OnDestroy();
        }
        m_scenes.clear();
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

    // Scene Management
    Scene *Engine::CreateScene(std::string name)
    {
        uint64_t id = IDManager<Scene>::GetNext();         // Create ID for the scene.
        auto newScene = std::make_unique<Scene>(id, name); // Create the scene locally.
        Scene *ptr = newScene.get();                       // Nude pointer to the scene.
        if (!m_activeScene)
            m_activeScene = ptr;
        m_scenes.push_back(std::move(newScene)); // Move the unique reference to the vector.
        return ptr;
    }
    Scene *Engine::CreateScene()
    {
        uint64_t id = IDManager<Scene>::GetNext();
        auto name = "Scene" + std::to_string(id);          // Create the name based on the id.
        auto newScene = std::make_unique<Scene>(id, name); // Create the scene locally.
        Scene *ptr = newScene.get();                       // Nude pointer to the scene.
        if (!m_activeScene)
            m_activeScene = ptr;
        m_scenes.push_back(std::move(newScene)); // Move the unique reference to the vector.
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

    // SDL Management
    void Engine::HandleSDLWindowEventPolling()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                // Se la finestra viene ridimensionata o massimizzata
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    width = event.window.data1;
                    height = event.window.data2;
                }
            }
        }
    }
    bool Engine::InitSDLWindowAndRenderer()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "Error while initializing SDL: " << SDL_GetError() << "\n";
            system("pause");
            return false;
        }

        // Window
        m_window = SDL_CreateWindow("SuperEngine",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (!m_window)
        {
            std::cout << "Error creating window: " << SDL_GetError() << std::endl;
            system("pause");
            return false;
        }
        // Renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if (!m_renderer)
        {
            std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
            system("pause");
            return false;
        }
        return true;
    }
}