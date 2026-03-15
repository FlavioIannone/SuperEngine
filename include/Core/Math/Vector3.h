#pragma once
#include <cmath>

namespace SuperEngine
{
    struct Vector3
    {

        float x, y, z;

        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 up;
        static const Vector3 right;
        static const Vector3 forward;

        Vector3 operator+(const Vector3 &other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        Vector3 operator-(const Vector3 &other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        float operator*(Vector3 other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 operator/(float scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }
    };

    inline const Vector3 Vector3::zero{0.0f, 0.0f, 0.0f};
    inline const Vector3 Vector3::one{1.0f, 1.0f, 1.0f};
    inline const Vector3 Vector3::up{0.0f, 1.0f, 0.0f};
    inline const Vector3 Vector3::right{1.0f, 0.0f, 0.0f};
    inline const Vector3 Vector3::forward{0.0f, 0.0f, 1.0f};
}