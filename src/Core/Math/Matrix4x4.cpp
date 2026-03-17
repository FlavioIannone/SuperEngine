#include "Core/Math/Vector4.h"
#include "Core/Math/Matrix4x4.h"
#include <cmath>

namespace SuperEngine
{
    Matrix4x4::Matrix4x4()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = 0.0f;
    }
    Matrix4x4 Matrix4x4::Identity()
    {
        Matrix4x4 matrix;
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        return matrix;
    }
    Vector4 Matrix4x4::MultiplyVector4(const Matrix4x4 &m, const Vector4 &i)
    {
        Vector4 v;
        v.x = i.x * m.m[0][0] + i.y * m.m[0][1] + i.z * m.m[0][2] + i.w * m.m[0][3];
        v.y = i.x * m.m[1][0] + i.y * m.m[1][1] + i.z * m.m[1][2] + i.w * m.m[1][3];
        v.z = i.x * m.m[2][0] + i.y * m.m[2][1] + i.z * m.m[2][2] + i.w * m.m[2][3];
        v.w = i.x * m.m[3][0] + i.y * m.m[3][1] + i.z * m.m[3][2] + i.w * m.m[3][3];
        return v;
    }
    Matrix4x4 Matrix4x4::GetProjectionMatrix(float aspectRatio, float fovFactor, float nearClip, float farClip)
    {
        Matrix4x4 p_m;
        float lambda = farClip / (farClip - nearClip);

        p_m.m[0][0] = fovFactor / aspectRatio;
        p_m.m[1][1] = fovFactor;
        p_m.m[2][2] = lambda;
        p_m.m[3][2] = 1.0f;
        p_m.m[2][3] = -lambda * (float)nearClip;
        p_m.m[3][3] = 0.0f;
        return p_m;
    }
}