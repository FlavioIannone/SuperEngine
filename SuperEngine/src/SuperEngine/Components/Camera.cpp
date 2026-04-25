#include "SuperEngine/Components/Camera.h"
#include "SuperEngine/Engine/Engine.h"
#include "SuperEngine/Components/Transform.h"
#include "SuperEngine/Math/Matrix4x4.h"
#include <cmath>

namespace SuperEngine
{
    double Camera::CalculateAspectRatio()
    {
        aspectRatio = static_cast<double>(Engine::GetInstance().GetWidth()) / static_cast<double>(Engine::GetInstance().GetHeight());
        return aspectRatio;
    }
    double Camera::CalculateFieldOfViewFactor()
    {
        double fov_rad = fieldOfView * M_PI / 180.0;
        fieldOfViewFactor = 1.0 / std::tan((fov_rad) / 2.0);
        return fieldOfViewFactor;
    }
    void Camera::CalculateFactors()
    {
        if (areFactorsDirty)
        {
            // Recalculate factors
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
    Camera::Camera(double fieldOfView, double nearClip, double farClip)
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
        if (transform->position != lastPosition || transform->rotation != lastRotation)
        {
            InvalidateViewMatrix();
            lastPosition = transform->position;
            lastRotation = transform->rotation;
        }
    }
    void Camera::Start()
    {
        transform = GetGameObject()->GetTransform();
    }
    const Matrix4x4 &Camera::CalculateViewMatrix()
    {
        if (isViewMatrixDirty)
        {
            isViewMatrixDirty = false;
            Matrix4x4 t = Matrix4x4::GetTranslationMatrix(-transform->position);
            Matrix4x4 r = Matrix4x4::TransposeMatrix(Matrix4x4::GetRotationMatrix(transform->rotation.x, transform->rotation.y, transform->rotation.z));
            m_viewMatrix = Matrix4x4::MultiplyMatrix(r, t);
        }
        return m_viewMatrix;
    }
}