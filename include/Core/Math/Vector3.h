#pragma once

namespace SuperEngine
{
    struct Vector3
    {

        float x, y, z;

        Vector3();
        Vector3(float _x, float _y, float _z);

        // Direction vectors
        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 up;
        static const Vector3 right;
        static const Vector3 forward;

        // Operators overload
        Vector3 operator+(const Vector3 &other) const;
        void operator+=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        void operator-=(const Vector3 &other);
        Vector3 operator*(float scalar) const;
        void operator*=(float scalar);
        float operator*(const Vector3 &other) const;
        void operator*=(const Vector3 &other);
        Vector3 operator/(float scalar) const;
        void operator/=(float scalar);
        bool operator!=(Vector3 other) const;
        bool operator==(Vector3 other) const;
    };

    inline const Vector3 Vector3::zero{0.0f, 0.0f, 0.0f};
    inline const Vector3 Vector3::one{1.0f, 1.0f, 1.0f};
    inline const Vector3 Vector3::up{0.0f, 1.0f, 0.0f};
    inline const Vector3 Vector3::right{1.0f, 0.0f, 0.0f};
    inline const Vector3 Vector3::forward{0.0f, 0.0f, 1.0f};
}