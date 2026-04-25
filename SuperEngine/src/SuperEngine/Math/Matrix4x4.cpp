#include "SuperEngine/Math/Vector4.h"
#include "SuperEngine/Math/Vector3.h"
#include "SuperEngine/Math/Matrix4x4.h"
#include <cmath>
#include <numbers>
namespace SuperEngine
{
    Matrix4x4::Matrix4x4()
    {
        m[0][0] = 0.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = 0.0f;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 0.0f;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 0.0f;
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
    Matrix4x4 Matrix4x4::MultiplyMatrix(const Matrix4x4 &m1, const Matrix4x4 &m2)
    {
        Matrix4x4 resMat;
        // First row
        resMat.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
        resMat.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
        resMat.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
        resMat.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
        // Second row
        resMat.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
        resMat.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
        resMat.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
        resMat.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
        // Third row
        resMat.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
        resMat.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
        resMat.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
        resMat.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
        // Forth row
        resMat.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
        resMat.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
        resMat.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
        resMat.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
        return resMat;
    }
    Matrix4x4 Matrix4x4::TransposeMatrix(const Matrix4x4 &m)
    {
        Matrix4x4 t;
        t.m[0][0] = m.m[0][0];
        t.m[0][1] = m.m[1][0];
        t.m[0][2] = m.m[2][0];
        t.m[0][3] = m.m[3][0];
        t.m[1][0] = m.m[0][1];
        t.m[1][1] = m.m[1][1];
        t.m[1][2] = m.m[2][1];
        t.m[1][3] = m.m[3][1];
        t.m[2][0] = m.m[0][2];
        t.m[2][1] = m.m[1][2];
        t.m[2][2] = m.m[2][2];
        t.m[2][3] = m.m[3][2];
        t.m[3][0] = m.m[0][3];
        t.m[3][1] = m.m[1][3];
        t.m[3][2] = m.m[2][3];
        t.m[3][3] = m.m[3][3];
        return t;
    }
    Matrix4x4 Matrix4x4::GetProjectionMatrix(double aspectRatio, double fovFactor, double nearClip, double farClip)
    {
        Matrix4x4 p_m = Matrix4x4();
        double lambda = farClip / (farClip - nearClip);

        p_m.m[0][0] = fovFactor / aspectRatio;
        p_m.m[1][1] = fovFactor;
        p_m.m[2][2] = lambda;
        p_m.m[3][2] = 1.0f;
        p_m.m[2][3] = -lambda * nearClip;
        p_m.m[3][3] = 0.0f;
        return p_m;
    }
    Matrix4x4 Matrix4x4::GetXRoationMatrix(double angle)
    {
        const double angleRad = angle * std::numbers::pi / 180.0;
        const double c = std::cos(angleRad);
        const double s = std::sin(angleRad);
        Matrix4x4 mat = Matrix4x4::Identity();
        mat.m[1][1] = c;
        mat.m[1][2] = -s;
        mat.m[2][1] = s;
        mat.m[2][2] = c;
        return mat;
    }
    Matrix4x4 Matrix4x4::GetYRoationMatrix(double angle)
    {
        const double angleRad = angle * std::numbers::pi / 180.0;
        const double c = std::cos(angleRad);
        const double s = std::sin(angleRad);
        Matrix4x4 mat = Matrix4x4::Identity();
        mat.m[0][0] = c;
        mat.m[0][2] = s;
        mat.m[2][0] = -s;
        mat.m[2][2] = c;
        return mat;
    }
    Matrix4x4 Matrix4x4::GetZRoationMatrix(double angle)
    {
        const double angleRad = angle * std::numbers::pi / 180.0;
        const double c = std::cos(angleRad);
        const double s = std::sin(angleRad);
        Matrix4x4 mat = Matrix4x4::Identity();
        mat.m[0][0] = c;
        mat.m[0][1] = -s;
        mat.m[1][0] = s;
        mat.m[1][1] = c;
        return mat;
    }
    Matrix4x4 Matrix4x4::GetRotationMatrix(double xAngle, double yAngle, double zAngle)
    {
        const Matrix4x4 r_x = GetXRoationMatrix(xAngle);
        const Matrix4x4 r_y = GetYRoationMatrix(yAngle);
        const Matrix4x4 r_z = GetZRoationMatrix(zAngle);
        Matrix4x4 mat = MultiplyMatrix(r_z, MultiplyMatrix(r_x, r_y));
        return mat;
    }

    Matrix4x4 Matrix4x4::GetTransformationMatrix(Vector3 translation, Vector3 rotation, Vector3 scale)
    {
        Matrix4x4 rotationMat = GetRotationMatrix(rotation.x, rotation.y, rotation.z);
        Matrix4x4 mat;
        // First row
        mat.m[0][0] = rotationMat.m[0][0] * scale.x;
        mat.m[0][1] = rotationMat.m[0][1] * scale.y;
        mat.m[0][2] = rotationMat.m[0][2] * scale.z;
        mat.m[0][3] = translation.x;
        // Second row
        mat.m[1][0] = rotationMat.m[1][0] * scale.x;
        mat.m[1][1] = rotationMat.m[1][1] * scale.y;
        mat.m[1][2] = rotationMat.m[1][2] * scale.z;
        mat.m[1][3] = translation.y;
        // Third row
        mat.m[2][0] = rotationMat.m[2][0] * scale.x;
        mat.m[2][1] = rotationMat.m[2][1] * scale.y;
        mat.m[2][2] = rotationMat.m[2][2] * scale.z;
        mat.m[2][3] = translation.z;
        // Forth row
        mat.m[3][0] = 0;
        mat.m[3][1] = 0;
        mat.m[3][2] = 0;
        mat.m[3][3] = 1;
        return mat;
    }

    Matrix4x4 Matrix4x4::GetTranslationMatrix(Vector3 t)
    {
        Matrix4x4 m = Identity();
        m.m[0][3] = t.x;
        m.m[1][3] = t.y;
        m.m[2][3] = t.z;
        return m;
    }

}