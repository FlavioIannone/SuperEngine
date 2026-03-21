#pragma once
#include <cmath>
#include "Core/Math/Vector2.h"

namespace SuperEngine
{

    float x, y;
    Vector2::Vector2() : x(0.0f), y(0.0f) {}
    Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

    Vector2 Vector2::operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    void Vector2::operator+=(const Vector2 &other)
    {
        this->x = this->x + other.x;
        this->y = this->y + other.y;
    }
    Vector2 Vector2::operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    void Vector2::operator-=(const Vector2 &other)
    {
        this->x = this->x - other.x;
        this->y = this->y - other.y;
    }
    Vector2 Vector2::operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }
    void Vector2::operator*=(const Vector2 &other)
    {
        this->x = this->x * other.x;
        this->y = this->y * other.y;
    }
    float Vector2::operator*(const Vector2 &other) const
    {
        return x * other.x + y * other.y;
    }
    void Vector2::operator*=(float scalar)
    {
        this->x = this->x * scalar;
        this->y = this->y * scalar;
    }
    Vector2 Vector2::operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }
    void Vector2::operator/=(float scalar)
    {
        this->x = this->x / scalar;
        this->y = this->y / scalar;
    }
    bool Vector2::operator!=(Vector2 other) const
    {
        return x != other.x || y != other.y;
    }
    bool Vector2::operator==(Vector2 other) const
    {
        return x == other.x && y == other.y;
    }

}