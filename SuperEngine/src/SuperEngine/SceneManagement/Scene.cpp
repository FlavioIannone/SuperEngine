#include "SuperEngine/SceneManagement/Scene.h"
#include "SuperEngine/IDManager.h"
#include "SuperEngine/Components/MeshRenderer.h"
#include "SuperEngine/Components/Camera.h"
#include "SuperEngine/Engine/AssetManager.h"

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
        // Call OnDestroy() on objects pending destruction while they are still safely allocated in memory.
        for (auto &obj : m_gameObjects)
        {
            if (obj->IsPendingDestroy())
            {
                obj->OnDestroy();
            }
        }

        // Physically remove the objects from the list.
        // The unique_ptrs going out of scope will automatically free the underlying memory.
        m_gameObjects.erase(
            std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
                           [](const std::unique_ptr<GameObject> &obj)
                           {
                               return obj->IsPendingDestroy();
                           }),
            m_gameObjects.end());

        // Tell the surviving game objects to clean up their own destroyed components.
        for (auto &obj : m_gameObjects)
        {
            obj->Cleanup();
        }
    }

    // GameObjects
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
    GameObject *Scene::CreateGameObject(std::string name, Vector3 pos)
    {
        uint64_t id = IDManager<GameObject>::GetNext();    // Create ID for the gameobject.
        auto obj = std::make_unique<GameObject>(id, name); // Create the gameobject locally.
        obj.get()->GetTransform()->position = pos;         // Translate the gameobject
        GameObject *ptr = obj.get();                       // Nude pointer to the obj.
        m_gameObjects.push_back(std::move(obj));           // Move the unique reference to the vector.
        return ptr;
    }
    GameObject *Scene::CreateGameObject(Vector3 pos)
    {
        uint64_t id = IDManager<GameObject>::GetNext();       // Create ID for the gameobject.
        std::string name = "GameObject" + std::to_string(id); // Create the name based on the id.
        auto obj = std::make_unique<GameObject>(id, name);    // Create the gameobject locally.
        obj.get()->GetTransform()->position = pos;            // Translate the gameobject
        GameObject *ptr = obj.get();                          // Nude pointer to the obj.
        m_gameObjects.push_back(std::move(obj));              // Move the unique reference to the vector.
        return ptr;
    }
    // Cube
    GameObject *Scene::CreateCube(std::string name, Vector3 pos)
    {
        GameObject *obj = CreateGameObject(name, pos);
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetCubeMeshFilepath());
        return obj;
    }
    GameObject *Scene::CreateCube(Vector3 pos)
    {
        GameObject *obj = CreateGameObject(pos);
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetCubeMeshFilepath());
        return obj;
    }
    GameObject *Scene::CreateCube(std::string name)
    {
        GameObject *obj = CreateGameObject(name);
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetCubeMeshFilepath());
        return obj;
    }
    GameObject *Scene::CreateCube()
    {
        GameObject *obj = CreateGameObject();
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetCubeMeshFilepath());
        return obj;
    }
    // Piramid
    GameObject *Scene::CreatePiramid(std::string name, Vector3 pos)
    {
        GameObject *obj = CreateGameObject(name, pos);
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetPiramidMeshFilepath());

        return obj;
    }
    GameObject *Scene::CreatePiramid(Vector3 pos)
    {
        GameObject *obj = CreateGameObject(pos);
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetPiramidMeshFilepath());

        return obj;
    }
    GameObject *Scene::CreatePiramid(std::string name)
    {
        GameObject *obj = CreateGameObject(name);
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetPiramidMeshFilepath());

        return obj;
    }
    GameObject *Scene::CreatePiramid()
    {
        GameObject *obj = CreateGameObject();
        obj->AddComponent<MeshRenderer>(AssetManager::GetInstance().GetPiramidMeshFilepath());
        return obj;
    }
    // Camera
    GameObject *Scene::CreateCamera(std::string name, Vector3 pos)
    {
        GameObject *obj = CreateGameObject(name, pos);
        obj->AddComponent<Camera>();
        return obj;
    }
    GameObject *Scene::CreateCamera(Vector3 pos)
    {
        GameObject *obj = CreateGameObject(pos);
        obj->AddComponent<Camera>();
        return obj;
    }
    GameObject *Scene::CreateCamera(std::string name)
    {
        GameObject *obj = CreateGameObject(name);
        obj->AddComponent<Camera>();
        return obj;
    }
    GameObject *Scene::CreateCamera()
    {
        GameObject *obj = CreateGameObject();
        obj->AddComponent<Camera>();
        return obj;
    }
}