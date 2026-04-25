#pragma once
#include "SuperEngine/Components/Component.h"
#include "SuperEngine/Components/Transform.h"
#include "SuperEngine/Math/Vector3.h"
#include "SuperEngine/Math/Matrix4x4.h"
#include <atomic>

namespace SuperEngine
{
    class Camera : public Component
    {
    private:
        // Flags:
        std::atomic<bool> areFactorsDirty = true;
        std::atomic<bool> isProjectionMatrixDirty = true;
        std::atomic<bool> isViewMatrixDirty = true;
        // Cached Values:
        double aspectRatio;
        double fieldOfView; // In degrees
        double fieldOfViewFactor;
        double nearClip;
        double farClip;
        Matrix4x4 m_projectionMatrix;
        Vector3 lastPosition;
        Vector3 lastRotation;
        Matrix4x4 m_viewMatrix;
        Transform *transform;

        // Window size
        int lastWindowWidth = 0;
        int lastWindowHeight = 0;

        // Reference to the main camera
        inline static Camera *m_main = nullptr;

        // Internal Methods
        double CalculateAspectRatio();
        double CalculateFieldOfViewFactor();
        // Invalidates the factors and the projection matrix cache.
        void InvalidateFactors()
        {
            areFactorsDirty = true;
            InvalidateProjectionMatrix(); // If the factors gets recalculated, the matrix must get recalculated too.
        }
        // Invalidates the view matrix cache.
        void InvalidateViewMatrix() { isViewMatrixDirty = true; }
        // Invalidates the projection matrix cache.
        void InvalidateProjectionMatrix() { isProjectionMatrixDirty = true; }
        void CalculateFactors();

    public:
        Camera();
        Camera(double, double, double);
        ~Camera();

        // Getters
        double GetAspectRatio() const { return aspectRatio; }
        double GetFieldOfViewFactor() const { return fieldOfViewFactor; }
        double GetNearClip() const { return nearClip; }
        double GetFarClip() const { return farClip; }
        inline static Camera *GetMainCamera() { return m_main; }

        // Setters
        void SetFieldOfView(double fieldOfView)
        {
            this->fieldOfView = fieldOfView;
            InvalidateProjectionMatrix();
        }

        // Public Methods
        void Update();
        void Start();
        const Matrix4x4 &CalculateProjectionMatrix();
        const Matrix4x4 &CalculateViewMatrix();
    };
}