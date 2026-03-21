#pragma once

namespace SuperEngine
{

    class ILifecycle
    {
    public:
        virtual ~ILifecycle() = default;

        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update() {}
        virtual void OnEnable() {}
        virtual void OnDisable() {}
        virtual void OnDestroy() {}
    };
}