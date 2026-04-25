#include "SuperEngine/Math/Vector4.h"

namespace SuperEngine
{
    // Initializes the vector to (0.0, 0.0, 0.0, 0.0)
    Vector4::Vector4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

    // Initializes the vector with specific x, y, z, and w values
    Vector4::Vector4(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}

    // Adds two vectors component-wise
    Vector4 Vector4::operator+(const Vector4 &other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Adds another vector to this vector component-wise in place
    void Vector4::operator+=(const Vector4 &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;
    }

    // Subtracts another vector from this vector component-wise
    Vector4 Vector4::operator-(const Vector4 &other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Negates the vector (inverts the sign of all components)
    Vector4 Vector4::operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }

    // Subtracts another vector from this vector in place
    void Vector4::operator-=(const Vector4 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;
    }

    // Multiplies the vector by a scalar value
    Vector4 Vector4::operator*(double scalar) const
    {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // Multiplies this vector by a scalar value in place
    void Vector4::operator*=(double scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        this->w *= scalar;
    }

    // Calculates the Dot Product (returns a scalar value)
    double Vector4::operator*(const Vector4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Multiplies this vector by another vector component-wise in place
    void Vector4::operator*=(const Vector4 &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        this->w *= other.w;
    }

    // Divides the vector by a scalar value
    Vector4 Vector4::operator/(double scalar) const
    {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    // Divides this vector by a scalar value in place
    void Vector4::operator/=(double scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        this->w /= scalar;
    }

    // Checks if two vectors are not exactly equal
    bool Vector4::operator!=(const Vector4 &other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    // Checks if two vectors are exactly equal
    bool Vector4::operator==(const Vector4 &other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
}