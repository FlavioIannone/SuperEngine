#include "Core/Components/Camera.h"
#include "Core/Engine/Engine.h"
#include "Core/Components/Transform.h"
#include "Core/Math/Matrix4x4.h"
#include <cmath>

namespace SuperEngine
{
    float Camera::CalculateAspectRatio()
    {
        aspectRatio = static_cast<float>(Engine::GetInstance().GetWidth()) / static_cast<float>(Engine::GetInstance().GetHeight());
        return aspectRatio;
    }
    float Camera::CalculateFieldOfViewFactor()
    {
        double fov_rad = fieldOfView * M_PI / 180.0f;
        fieldOfViewFactor = 1.0f / (float)std::tan(fov_rad / 2.0f);
        return fieldOfViewFactor;
    }
    void Camera::CalculateFactors()
    {
        if (areFactorsDirty)
        {
            // Recalculate flags
            CalculateAspectRatio();
            CalculateFieldOfViewFactor();
            areFactorsDirty = false;
        }
    }
    const Matrix4x4 &Camera::CalculateProjectionMatrix()
    {
        if (areFactorsDirty)
            CalculateFactors();
        if (isProjectionMatrixDirty)
        {
            m_projectionMatrix = Matrix4x4::GetProjectionMatrix(aspectRatio, fieldOfViewFactor, nearClip, farClip);
        }

        return m_projectionMatrix;
    }
    Camera::Camera()
    {
        fieldOfView = 70.0f;
        nearClip = 0.1f;
        farClip = 1000.0f;
        if (!m_main)
        {
            m_main = this;
        }
    }
    Camera::Camera(float fieldOfView, float nearClip, float farClip)
    {
        this->fieldOfView = fieldOfView;
        this->nearClip = nearClip;
        this->farClip = farClip;
        if (!m_main)
        {
            m_main = this;
        }
    }
    Camera::~Camera()
    {
        if (m_main == this)
        {
            m_main = nullptr;
        }
    }
    void Camera::Update()
    {
        if (Engine::GetInstance().GetWidth() != lastWindowWidth || Engine::GetInstance().GetHeight() != lastWindowHeight)
        {
            InvalidateFactors();
            lastWindowWidth = Engine::GetInstance().GetWidth();
            lastWindowHeight = Engine::GetInstance().GetHeight();
        }
    }
}