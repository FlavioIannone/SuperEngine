#pragma once

namespace SuperEngine
{
    struct Vector4
    {
        float x, y, z, w;
        Vector4();
        Vector4(float _x, float _y, float _z, float _w);

        // Direction vectors
        static const Vector4 zero;
        static const Vector4 one;
        static const Vector4 up;
        static const Vector4 right;
        static const Vector4 forward;

        // Operators overload
        Vector4 operator+(const Vector4 &other) const;
        void operator+=(const Vector4 &other);
        Vector4 operator-(const Vector4 &other) const;
        void operator-=(const Vector4 &other);
        Vector4 operator*(float scalar) const;
        void operator*=(float scalar);
        float operator*(const Vector4 &other) const;
        void operator*=(const Vector4 &other);
        Vector4 operator/(float scalar) const;
        void operator/=(float scalar);
        bool operator!=(Vector4 other) const;
        bool operator==(Vector4 other) const;
    };

    inline const Vector4 Vector4::zero{0.0f, 0.0f, 0.0f, 0.0f};
    inline const Vector4 Vector4::one{1.0f, 1.0f, 1.0f, 1.0f};
    inline const Vector4 Vector4::up{0.0f, 1.0f, 0.0f, 0.0f};
    inline const Vector4 Vector4::right{1.0f, 0.0f, 0.0f, 0.0f};
    inline const Vector4 Vector4::forward{0.0f, 0.0f, 1.0f, 0.0f};
}