#pragma once
#include <cmath>

namespace SuperEngine
{
    struct Vector2
    {

        float x, y;
        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float _x, float _y) : x(_x), y(_y) {}

        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 up;
        static const Vector2 right;

        Vector2 operator+(const Vector2 &other) const
        {
            return Vector2(x + other.x, y + other.y);
        }
        Vector2 operator-(const Vector2 &other) const
        {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator*(float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }

        float operator*(Vector2 other) const
        {
            return x * other.x + y * other.y;
        }

        Vector2 operator/(float scalar) const
        {
            return Vector2(x / scalar, y / scalar);
        }
    };

    inline const Vector2 Vector2::zero{0.0f, 0.0f};
    inline const Vector2 Vector2::one{1.0f, 1.0f};
    inline const Vector2 Vector2::up{0.0f, 1.0f};
    inline const Vector2 Vector2::right{1.0f, 0.0f};
}