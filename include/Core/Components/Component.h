#pragma once
namespace SuperEngine
{
    class GameObject;

    class Component
    {
    private:
        GameObject *m_gameObject = nullptr;
        bool isEnabled = true;

    public:
        virtual void Start() {};
        virtual void Update() {};
        virtual ~Component() = default;
        void SetGameObject(GameObject *owner) { m_gameObject = owner; }
        GameObject *GetGameObject() const { return m_gameObject; }
        bool IsEnabled() const { return isEnabled; }
        void Enable() { isEnabled = true; }
        void Disable() { isEnabled = false; }
    };
}