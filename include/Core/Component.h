#pragma once
namespace SuperEngine
{
    class GameObject;

    class Component
    {
    private:
        GameObject *gameObject = nullptr;
        bool isEnabled = true;

    public:
        virtual void Init();
        virtual void Update();
        virtual void Destroy();
    };
}