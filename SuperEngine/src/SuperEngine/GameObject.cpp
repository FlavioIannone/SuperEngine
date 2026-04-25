#include "SuperEngine/GameObject.h"
#include "SuperEngine/Components/Transform.h"
#include <string>
namespace SuperEngine
{
    void GameObject::Awake()
    {
        for (auto &comp : m_components)
        {
            if (comp->IsEnabled())
            {
                comp->Awake();
            }
        }
    }
    void GameObject::Start()
    {
        hasCalledStart = true;
        for (auto &comp : m_components)
        {
            // If the comp is disabled, call it's start OnEnable.
            if (comp->IsEnabled())
            {
                comp->Start();
            }
        }
    }
    void GameObject::Update()
    {
        for (auto &comp : m_components)
        {
            if (comp->IsEnabled())
            {
                comp->Update();
            }
        }
    }
    void GameObject::OnEnable()
    {
        if (!hasCalledStart)
            Start();
        for (auto &comp : m_components)
        {
            if (comp->IsEnabled())
            {
                comp->OnEnable();
            }
        }
    }
    void GameObject::OnDisable()
    {
        for (auto &comp : m_components)
        {
            if (comp->IsEnabled())
            {
                comp->OnDisable();
            }
        }
    }
    void GameObject::OnDestroy()
    {
        for (auto &comp : m_components)
        {
            comp->OnDestroy();
        }
    }
    void GameObject::Cleanup()
    {
        // Call OnDestroy() on components pending destruction while they are still safely allocated in memory.
        for (auto &comp : m_components)
        {
            if (comp->IsPendingDestroy())
            {
                comp->OnDestroy();
            }
        }
        // Physically remove the components from the list.
        // The unique_ptrs going out of scope will automatically free the underlying memory.
        m_components.erase(
            std::remove_if(m_components.begin(), m_components.end(),
                           [](const std::unique_ptr<Component> &comp)
                           {
                               return comp->IsPendingDestroy();
                           }),
            m_components.end());
    }

    GameObject::GameObject(uint64_t id, std::string _name)
    {
        m_id = id;
        m_name = _name;
        if (!m_transform)
            m_transform = AddComponent<Transform>();
    }
    GameObject::GameObject(uint64_t id)
    {
        m_id = id;
        m_name = "GameObject" + std::to_string(id);
        if (!m_transform)
            m_transform = AddComponent<Transform>();
    }
}