#pragma once
#include "Core/Core.h"
#include <iostream>
using namespace SuperEngine;

class TestScript : public Component
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

            float time = (float)Time::GetInstance().GetTotalTime();
            float dt = (float)Time::GetInstance().GetDeltaTime();

            transform->position += Vector3(std::sin(time) * speed * dt, 0, std::sin(time) * speed * dt);
            std::cout << "position: x=" << transform->position.x << " y=" << transform->position.y << " z=" << transform->position.z << ".\n";
        }
        else
        {

            std::cout << "[Warning] " << owner->GetName() << " non ha un Transform!\n";
        }
    }
};
