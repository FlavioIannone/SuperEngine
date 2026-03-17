#pragma once
#include <atomic>
#include <memory>
#include <string>
#include <vector>
#include "../GameObject.h"

namespace SuperEngine
{
    class Scene
    {
    private:
        std::atomic<bool> isEnabled = true;
        std::vector<std::unique_ptr<GameObject>> m_gameObjects;
        uint64_t m_id;
        std::string m_name = "Scene";

    public:
        // Constructors
        Scene(uint64_t, std::string);
        Scene(uint64_t);
        // Destructure
        ~Scene() = default;

        // Getters
        std::string GetName() const { return m_name; }
        uint64_t GetId() const { return m_id; }
        bool IsEnabled() const { return isEnabled; }

        // Setters
        void SetName(std::string name) { m_name = name; }
        void Enable() { isEnabled = true; }
        void Disable() { isEnabled = false; }

        // Methods
        void Update();

        GameObject *CreateGameObject(std::string);
        GameObject *CreateGameObject();
    };
}