#pragma once
#include "SuperEngine/SuperEngine.h"
#include <iostream>
using namespace SuperEngine;

class TestScript : public Component
{
public:
    Vector3 initialPosition;
    double radius = 3.0;
    double angularSpeed = 50;

    void Start() override
    {
        GameObject *owner = GetGameObject();
        if (!owner)
            return;

        Transform *transform = GetGameObject()->GetTransform();
        initialPosition = transform->position;
    }

    void Update() override
    {
        GameObject *owner = GetGameObject();
        if (!owner)
            return;

        Transform *transform = owner->GetTransform();

        if (transform)
        {
            srand(static_cast<unsigned>(time(nullptr)));

            float time = static_cast<float>(Time::GetInstance().GetTotalTime());
            float dt = static_cast<float>(Time::GetInstance().GetDeltaTime());

            // transform->position = initialPosition + Vector3(
            //                                             std::cos(time * angularSpeed) * radius,
            //                                             std::sin(time * angularSpeed) * radius,
            //                                             0.0);
            int rX = static_cast<int>(rand()) / static_cast<int>(RAND_MAX) * 2 - 1;
            int rY = static_cast<int>(rand()) / static_cast<int>(RAND_MAX) * 2 - 1;
            int rZ = static_cast<int>(rand()) / static_cast<int>(RAND_MAX) * 2 - 1;

            transform->rotation += Vector3(sin(dt) * rX * angularSpeed, sin(dt) * rY * angularSpeed, sin(dt) * rZ * angularSpeed);
        }
        else
        {

            std::cout << "[Warning] " << owner->GetName() << " non ha un Transform!\n";
        }
    }
};
