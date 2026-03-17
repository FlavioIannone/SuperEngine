#pragma once
#include "Core/Math/Vector4.h"

namespace SuperEngine
{
    Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

    Vector4 Vector4::operator+(const Vector4 &other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    Vector4 Vector4::operator-(const Vector4 &other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    Vector4 Vector4::operator*(float scalar) const
    {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    float Vector4::operator*(Vector4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    Vector4 Vector4::operator/(float scalar) const
    {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }
    bool Vector4::operator!=(Vector4 other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }
    bool Vector4::operator==(Vector4 other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
}