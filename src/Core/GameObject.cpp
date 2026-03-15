#include "Core/GameObject.h"
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
    }

    GameObject::GameObject(uint64_t id)
    {
        m_id = id;
        m_name = "GameObject" + std::to_string(id);
    }
}