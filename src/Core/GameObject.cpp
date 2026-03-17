#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include <string>
namespace SuperEngine
{
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