#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include <string>
#include <atomic>
#include "Components/Component.h"

namespace SuperEngine
{

    class GameObject
    {
    private:
        uint64_t m_id;
        std::string m_name = "GameObject";
        std::vector<std::unique_ptr<Component>> m_components;
        std::atomic<bool> isEnabled = true;

    public:
        // Constructors
        GameObject(uint64_t, std::string);
        GameObject(uint64_t);
        // Destructure
        ~GameObject() = default;

        // Getters
        std::string GetName() const { return m_name; }

        uint64_t GetId() const { return m_id; }

        bool IsEnabled() const { return isEnabled; }

        // Setters
        void SetName(std::string name) { m_name = name; }

        void Enable() { isEnabled = true; }

        void Disable() { isEnabled = false; }

        // Methods
        template <typename T, typename... Args>
        T *AddComponent(Args &&...args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derivate from Component.");
            std::unique_ptr<T> newComponent = std::make_unique<T>(std::forward<Args>(args)...);
            T *ptr = newComponent.get();

            ptr->SetGameObject(this);
            m_components.push_back(std::move(newComponent));

            ptr->Start();
            return ptr;
        }

        template <typename T>
        T *GetComponent()
        {
            for (auto &comp : m_components)
            {
                T *target = dynamic_cast<T *>(comp.get());
                if (target)
                    return target;
            }
            return nullptr;
        }

        void Update();
    };
}