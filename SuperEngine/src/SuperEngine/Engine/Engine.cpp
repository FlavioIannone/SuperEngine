#include "SuperEngine/Engine/Engine.h"
#include "SuperEngine/Time.h"
#include "SuperEngine/IDManager.h"
#include <string>
#include <iostream>
#include "SuperEngine/Engine/RenderingManager.h"
#include "SuperEngine/Graphics/ComputeShader.h"

namespace SuperEngine
{
    bool Engine::Init(int width, int height, bool isVSyncActive)
    {
        // This is the first frame
        isFirstFrame = true;
        this->width = width;
        this->height = height;
        this->isVSyncActive = isVSyncActive;
        builtInShaders = std::make_unique<BuiltInShaders>();
        if (!InitSDLWindowAndGPUDevice())
        {
            return false;
        }

        // Load the shaders
        if (!GetBuiltInShaders()->InitShaders())
            return false;

        isRunning = true;
        std::cout << "Engine started.\n";
        return true;
    }

    void Engine::Run()
    {
        isFirstFrame = false;
        // Call awake for the scenes.
        for (auto &scene : m_scenes)
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
            static double timeout = 1;
            Time::GetInstance().Tick();
            if (timeout <= 0)
            {
                std::cout << "FPS: " << static_cast<int>(1.0 / Time::GetInstance().GetDeltaTime()) << std::endl;
                timeout = 1;
            }
            timeout -= Time::GetInstance().GetDeltaTime();

            HandleSDLWindowEventPolling();
            // Calling update for each scene.
            if (m_activeScene != nullptr && m_activeScene->IsEnabled())
            {
                m_activeScene->Update();
            }

            // Draw phase
            RenderingManager::GetInstance().Render();

            // Flip the buffers to present the result
            if (graphicsDevice)
            {
                graphicsDevice->Present();
            }

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
                // If the windows gets resized
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    width = event.window.data1;
                    height = event.window.data2;
                    if (graphicsDevice)
                        GetGraphicsDevice()->Resize();
                }
            }
        }
    }
    bool Engine::InitSDLWindowAndGPUDevice()
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
        // Initialize DirectX device.
        graphicsDevice = std::make_unique<GraphicsDevice>();
        if (!graphicsDevice->Initialize(m_window, width, height))
        {
            std::cerr << "Error initializing DirectX 11" << std::endl;
            return false;
        }

        return true;
    }

}