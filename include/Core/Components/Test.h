#pragma once
#include "Component.h"
#include "../GameObject.h"
#include "Transform.h"
#include "../Time.h"
#include <iostream>

namespace SuperEngine
{
    class Test : public Component
    {
    public:
        float speed = 2.0f;

        void Update() override
        {
            GameObject *owner = GetGameObject();
            if (!owner)
                return;

            Transform *transform = owner->GetComponent<Transform>();

            if (transform)
            {

                float dt = (float)Time::GetInstance().GetDeltaTime();

                transform->position = transform->position + (Vector3::forward * speed * dt);

                std::cout << "Oggetto: " << owner->GetName()
                          << " | Pos Z: " << transform->position.z << "\n";
            }
            else
            {

                std::cout << "[Warning] " << owner->GetName() << " non ha un Transform!\n";
            }
        }
    };
}