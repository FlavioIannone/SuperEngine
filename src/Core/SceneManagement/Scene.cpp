#include "Core/SceneManagement/Scene.h"
#include "Core/IDManager.h"

namespace SuperEngine
{
    Scene::Scene(uint64_t id, std::string name)
    {
        m_id = id;
        m_name = name;
    }
    Scene::Scene(uint64_t id)
    {
        m_id = id;
        m_name = "Scene" + std::to_string(id);
    }
    void Scene::Awake()
    {
        for (auto &obj : m_gameObjects)
        {
            if (obj->IsEnabled())
            {
                obj->Awake();
            }
        }
    }
    void Scene::Start()
    {
        hasCalledStart = true;
        for (auto &obj : m_gameObjects)
        {
            // If the obj's is disabled, call it's start OnEnable.
            if (obj->IsEnabled())
            {
                obj->Start();
            }
        }
    }
    void Scene::Update()
    {
        for (auto &obj : m_gameObjects)
        {
            if (obj->IsEnabled())
            {
                obj->Update();
            }
        }
    }
    void Scene::OnEnable()
    {
        if (!hasCalledStart)
            Start();

        for (auto &obj : m_gameObjects)
        {
            if (obj->IsEnabled())
            {
                obj->OnEnable();
            }
        }
    }
    void Scene::OnDisable()
    {
        for (auto &obj : m_gameObjects)
        {
            if (obj->IsEnabled())
            {
                obj->OnDisable();
            }
        }
    }
    void Scene::OnDestroy()
    {
        for (auto &obj : m_gameObjects)
        {
            obj->OnDestroy();
        }
    }

    void Scene::Cleanup()
    {
        // Phase 1: Call OnDestroy() on objects pending destruction while they are still safely allocated in memory.
        for (auto &obj : m_gameObjects)
        {
            if (obj->IsPendingDestroy())
            {
                obj->OnDestroy();
            }
        }

        // Phase 2: Physically remove the objects from the list.
        // The unique_ptrs going out of scope will automatically free the underlying memory.
        m_gameObjects.erase(
            std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
                           [](const std::unique_ptr<GameObject> &obj)
                           {
                               return obj->IsPendingDestroy();
                           }),
            m_gameObjects.end());

        // Phase 3: Tell the surviving game objects to clean up their own destroyed components.
        for (auto &obj : m_gameObjects)
        {
            obj->Cleanup();
        }
    }

    GameObject *Scene::CreateGameObject(std::string name)
    {
        uint64_t id = IDManager<GameObject>::GetNext();    // Create ID for the gameobject.
        auto obj = std::make_unique<GameObject>(id, name); // Create the gameobject locally.
        GameObject *ptr = obj.get();                       // Nude pointer to the obj.
        m_gameObjects.push_back(std::move(obj));           // Move the unique reference to the vector.
        return ptr;
    }
    GameObject *Scene::CreateGameObject()
    {
        uint64_t id = IDManager<GameObject>::GetNext();       // Create ID for the gameobject.
        std::string name = "GameObject" + std::to_string(id); // Create the name based on the id.
        auto obj = std::make_unique<GameObject>(id, name);    // Create the gameobject locally.
        GameObject *ptr = obj.get();                          // Nude pointer to the obj.
        m_gameObjects.push_back(std::move(obj));              // Move the unique reference to the vector.
        return ptr;
    }
}