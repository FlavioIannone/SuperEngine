#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Component.h"

namespace SuperEngine
{
    class GameObject
    {
    private:
        std::uint64_t id;
        std::string name = "GameObject";
        std::vector<std::unique_ptr<Component>> components;

    public:
        template <typename T>
        void AddComponent();

        template <typename T>
        T *GetComponent();

        void Update();
    };
}