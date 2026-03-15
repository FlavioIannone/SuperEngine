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

    GameObject *Scene::CreateGameObject(std::string name)
    {
        uint64_t id = IDManager<GameObject>::GetNext();
        auto obj = std::make_unique<GameObject>(id, name);
        GameObject *ptr = obj.get();
        m_gameObjects.push_back(std::move(obj));
        return ptr;
    }

    GameObject *Scene::CreateGameObject()
    {
        uint64_t id = IDManager<GameObject>::GetNext();
        std::string name = "GameObject" + std::to_string(id);
        GameObject *ptr = CreateGameObject(name);
        return ptr;
    }
}