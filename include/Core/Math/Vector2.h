#pragma once

namespace SuperEngine
{
    struct Vector2
    {

        float x, y;
        Vector2();
        Vector2(float, float);

        // Direction vectors
        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 up;
        static const Vector2 right;

        // Operators overload
        Vector2 operator+(const Vector2 &other) const;
        void operator+=(const Vector2 &other);
        Vector2 operator-(const Vector2 &other) const;
        void operator-=(const Vector2 &other);
        Vector2 operator*(float scalar) const;
        void operator*=(float scalar);
        float operator*(const Vector2 &other) const;
        void operator*=(const Vector2 &other);
        Vector2 operator/(float scalar) const;
        void operator/=(float scalar);
        bool operator!=(Vector2 other) const;
        bool operator==(Vector2 other) const;
    };

    inline const Vector2 Vector2::zero{0.0f, 0.0f};
    inline const Vector2 Vector2::one{1.0f, 1.0f};
    inline const Vector2 Vector2::up{0.0f, 1.0f};
    inline const Vector2 Vector2::right{1.0f, 0.0f};
}