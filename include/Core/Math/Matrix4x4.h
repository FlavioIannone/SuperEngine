#pragma once
#include "Vector4.h"

namespace SuperEngine
{
    struct Matrix4x4
    {
    private:
        float m[4][4] = {0.0f};

    public:
        Matrix4x4();
        // Returns the identity matrix.
        static Matrix4x4 Identity();
        // Multiplies a Matrix4x4 and a Vector4.
        static Vector4 MultiplyVector4(const Matrix4x4 &m, const Vector4 &i);
        // Returns a projection matrix.
        static Matrix4x4 GetProjectionMatrix(float aspectRatio, float fovFactor, float nearClip, float farClip);
    };
}