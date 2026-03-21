#include "Core/Components/Transform.h"

namespace SuperEngine
{
    Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        isIndestructible = true;
    }
}