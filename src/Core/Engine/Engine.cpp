#include "Core/Engine/Engine.h"
#include "Core/Time.h"
#include "Core/IDManager.h"
#include <string>
#include <iostream>

namespace SuperEngine
{
    void Engine::Run()
    {
        while (isRunning)
        {
            Time::GetInstance().Tick();
            if (m_activeScene != nullptr && m_activeScene->IsEnabled())
            {
                m_activeScene->Update();
            }
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