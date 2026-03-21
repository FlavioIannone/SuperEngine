#pragma once
#include <atomic>
#include <memory>
#include <string>
#include <vector>
#include "../GameObject.h"
#include "../ILifecycle.h"

namespace SuperEngine
{
    class Scene : public ILifecycle
    {
    private:
        uint64_t m_id;
        std::string m_name = "Scene";
        std::atomic<bool> isEnabled = true;
        std::atomic<bool> hasCalledStart = false;
        std::vector<std::unique_ptr<GameObject>> m_gameObjects;

    public:
        // Constructors
        Scene(uint64_t, std::string);
        Scene(uint64_t);
        // Destructor
        ~Scene() = default;

        // Getters
        std::string GetName() const { return m_name; }
        uint64_t GetId() const { return m_id; }
        bool IsEnabled() const { return isEnabled; }

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

        // Lifecycle methods
        void Awake();
        void Start();
        void Update();
        void OnDestroy();
        void OnEnable();
        void OnDisable();

        void Cleanup();

        GameObject *CreateGameObject(std::string);
        GameObject *CreateGameObject();
    };
}