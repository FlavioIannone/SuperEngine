#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include <string>
#include <atomic>
#include "SuperEngine/Components/Component.h"
#include "SuperEngine/Components/Transform.h"
#include "SuperEngine/ILifecycle.h"

namespace SuperEngine
{

    class GameObject : public ILifecycle
    {
    private:
        uint64_t m_id;
        std::string m_name = "GameObject";

        std::vector<std::unique_ptr<Component>> m_components;
        Transform *m_transform = nullptr;
        std::atomic<bool> isEnabled = true;
        std::atomic<bool> hasCalledStart = false;

    protected:
        std::atomic<bool> m_pendingDestroy = false;

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
        Transform *GetTransform() const { return m_transform; }

        // Setters
        void SetName(std::string name) { m_name = name; }
        void Enable()
        {
            isEnabled = true;
            OnEnable();
        }
        void Disable()
        {
            isEnabled = false;
            OnDisable();
        }

        // Methods
        template <typename T, typename... Args>
        T *AddComponent(Args &&...args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derivate from Component.");
            std::unique_ptr<T> newComponent = std::make_unique<T>(std::forward<Args>(args)...);
            T *ptr = newComponent.get();

            ptr->SetGameObject(this);
            m_components.push_back(std::move(newComponent));

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
        // Lifecycle methods

        void Awake();
        void Start();
        void Update();
        void OnDestroy();
        void OnEnable();
        void OnDisable();

        void Cleanup();

        void Destroy() { m_pendingDestroy = true; }
        bool IsPendingDestroy() const { return m_pendingDestroy; }
    };
}