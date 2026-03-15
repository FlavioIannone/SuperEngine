#pragma once
#include "Component.h"
#include "../Math/Vector3.h"

namespace SuperEngine
{
    class Transform : public Component
    {
    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

    public:
        Transform(Vector3 pos = Vector3::zero,
                  Vector3 rot = Vector3::zero,
                  Vector3 scl = Vector3::one);
    };
}