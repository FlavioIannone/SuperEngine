#pragma once
#include "../ILifecycle.h"
#include <iostream>
#include <atomic>
namespace SuperEngine
{
    class GameObject;

    class Component : public ILifecycle
    {
    private:
        GameObject *m_gameObject = nullptr;
        std::atomic<bool> isEnabled = true;

    protected:
        std::atomic<bool> m_pendingDestroy = false;
        std::atomic<bool> isIndestructible = true;

    public:
        // Lifecycle methods
        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update() {};
        virtual void OnDestroy() {};
        virtual void OnEnable() {};
        virtual void OnDisable() {};

        void Destroy()
        {
            if (!isIndestructible)
                m_pendingDestroy = true;
            else
                std::cout << "[Warning] Attempted to destroy an indestructible core component!\n";
        }
        bool IsPendingDestroy() const { return m_pendingDestroy; }

        virtual ~Component() = default;
        void SetGameObject(GameObject *owner) { m_gameObject = owner; }
        GameObject *GetGameObject() const { return m_gameObject; }
        bool IsEnabled() const { return isEnabled; }
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
    };
}