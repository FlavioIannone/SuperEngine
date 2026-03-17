#pragma once
#include "Component.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include <atomic>

namespace SuperEngine
{
    class Camera : public Component
    {
    private:
        // Flags:
        std::atomic<bool> areFactorsDirty = true;
        std::atomic<bool> isProjectionMatrixDirty = true;
        // Cached Values:
        float aspectRatio;
        float fieldOfView; // In degrees
        float fieldOfViewFactor;
        float nearClip;
        float farClip;
        Matrix4x4 m_projectionMatrix;

        // Window size
        int lastWindowWidth = 0;
        int lastWindowHeight = 0;

        // Reference to the main camera
        inline static Camera *m_main = nullptr;

        // Internal Methods
        float CalculateAspectRatio();
        float CalculateFieldOfViewFactor();
        // Invalidates the factors and the projection matrix cache.
        void InvalidateFactors()
        {
            areFactorsDirty = true;
            InvalidateProjectionMatrix(); // If the factors gets recalculated, the matrix must get recalculated too.
        }
        // Invalidates the projection matrix cache.
        void InvalidateProjectionMatrix() { isProjectionMatrixDirty = true; }
        void CalculateFactors();

    public:
        Camera();
        Camera(float, float, float);
        ~Camera();

        // Getters
        float GetAspectRatio() const { return aspectRatio; }
        float GetFieldOfViewFactor() const { return fieldOfViewFactor; }
        float GetNearClip() const { return nearClip; }
        float GetFarClip() const { return farClip; }
        inline static Camera *GetMainCamera() { return m_main; }

        // Setters
        void SetFieldOfView(float fieldOfView)
        {
            this->fieldOfView = fieldOfView;
            InvalidateProjectionMatrix();
        }

        // Public Methods
        void Update();
        const Matrix4x4 &CalculateProjectionMatrix();
    };
}