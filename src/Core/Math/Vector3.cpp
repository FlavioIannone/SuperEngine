#pragma once
#include <cmath>
#include "Core/Math/Vector3.h"

namespace SuperEngine
{

    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    Vector3 Vector3::operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    float Vector3::operator*(Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector3 Vector3::operator/(float scalar) const
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
    bool Vector3::operator!=(Vector3 other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }
    bool Vector3::operator==(Vector3 other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};
