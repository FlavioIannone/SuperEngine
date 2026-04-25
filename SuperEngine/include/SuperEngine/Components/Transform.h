#pragma once
#include "SuperEngine/Components/Component.h"
#include "SuperEngine/Math/Vector3.h"
#include "SuperEngine/Math/Matrix4x4.h"
#include <atomic>

namespace SuperEngine
{
    class Transform : public Component
    {
    private:
        // Flag
        std::atomic<bool> isTransformationMatrixDirty = true;

        // Scarthpad values for cache invalidation
        Vector3 lastPosition = Vector3::zero;
        Vector3 lastRotation = Vector3::zero;
        Vector3 lastScale = Vector3::zero;
        Matrix4x4 transformationMatrix;

        // Internal methods
        void InvalidateTransformationMatrix() { isTransformationMatrixDirty = true; }

    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

    public:
        Transform(Vector3 pos = Vector3::zero,
                  Vector3 rot = Vector3::zero,
                  Vector3 scl = Vector3::one);
        void Update() override;
        const Matrix4x4 &CalculateTransformationMatrix();
    };
}