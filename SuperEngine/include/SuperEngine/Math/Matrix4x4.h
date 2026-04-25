#pragma once
#include "SuperEngine/Math/Vector4.h"
#include <array>

namespace SuperEngine
{
    struct Matrix4x4
    {
    private:
        double m[4][4] = {0.0f};

    public:
        Matrix4x4();
        // Returns the identity matrix.
        static Matrix4x4 Identity();
        // Multiplies a Matrix4x4 and a Vector4.
        static Vector4 MultiplyVector4(const Matrix4x4 &m, const Vector4 &i);
        // Multiplies two Matrix4x4.
        static Matrix4x4 MultiplyMatrix(const Matrix4x4 &m1, const Matrix4x4 &m2);
        // Transposes a Matrix4x4
        static Matrix4x4 TransposeMatrix(const Matrix4x4 &m);
        // Returns a projection matrix.
        static Matrix4x4 GetProjectionMatrix(double aspectRatio, double fovFactor, double nearClip, double farClip);
        // Returns a rotation matrix around the X axis, the angle is in degrees
        static Matrix4x4 GetXRoationMatrix(double angle);
        // Returns a rotation matrix around the Y axis, the angle is in degrees
        static Matrix4x4 GetYRoationMatrix(double angle);
        // Returns a rotation matrix around the Z axis, the angle is in degrees
        static Matrix4x4 GetZRoationMatrix(double angle);
        // Returns a rotation matrix around the XYZ axis, the angles are in degrees
        static Matrix4x4 GetRotationMatrix(double xAngle, double yAngle, double zAngle);
        // Returns a transformation matrix
        static Matrix4x4 GetTransformationMatrix(Vector3 translation, Vector3 rotation, Vector3 scale);
        // Returns a translation matrix
        static Matrix4x4 GetTranslationMatrix(Vector3 t);
        // Returns the matrix flatten
        template <typename T>
        static std::array<T, 16> GetFlattenMatrix(const Matrix4x4 &mat)
        {
            return {
                static_cast<T>(mat.m[0][0]), static_cast<T>(mat.m[0][1]), static_cast<T>(mat.m[0][2]), static_cast<T>(mat.m[0][3]),
                static_cast<T>(mat.m[1][0]), static_cast<T>(mat.m[1][1]), static_cast<T>(mat.m[1][2]), static_cast<T>(mat.m[1][3]),
                static_cast<T>(mat.m[2][0]), static_cast<T>(mat.m[2][1]), static_cast<T>(mat.m[2][2]), static_cast<T>(mat.m[2][3]),
                static_cast<T>(mat.m[3][0]), static_cast<T>(mat.m[3][1]), static_cast<T>(mat.m[3][2]), static_cast<T>(mat.m[3][3])};
        }
    };
}