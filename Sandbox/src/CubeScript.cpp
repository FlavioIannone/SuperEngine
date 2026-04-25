#pragma once
#include "SuperEngine/SuperEngine.h"
#include <iostream>
using namespace SuperEngine;

class CubeScript : public Component
{
public:
    double angularSpeed = 50;

    void Update() override
    {
        GameObject *owner = GetGameObject();
        if (!owner)
            return;

        Transform *transform = owner->GetTransform();

        if (transform)
        {

            float time = static_cast<float>(Time::GetInstance().GetTotalTime());

            transform->rotation.y += sin(Time::GetInstance().GetDeltaTime()) * angularSpeed;
        }
        else
        {

            std::cout << "[Warning] " << owner->GetName() << " non ha un Transform!\n";
        }
    }
};
