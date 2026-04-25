#include "SuperEngine/Components/Transform.h"

namespace SuperEngine
{
    Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        isIndestructible = true;
    }

    const Matrix4x4 &Transform::CalculateTransformationMatrix()
    {
        if (isTransformationMatrixDirty)
        {
            transformationMatrix = Matrix4x4::GetTransformationMatrix(position, rotation, scale);
            isTransformationMatrixDirty = false;
        }
        return transformationMatrix;
    }

    void Transform::Update()
    {
        if (position != lastPosition || rotation != lastRotation || scale != lastScale)
        {
            InvalidateTransformationMatrix();
            lastPosition = position;
            lastRotation = rotation;
            lastScale = scale;
        }
    }
}