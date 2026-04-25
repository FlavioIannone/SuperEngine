#include <cmath>
#include "SuperEngine/Math/Vector3.h"

namespace SuperEngine
{
    // Initializes the vector to (0.0, 0.0, 0.0)
    Vector3::Vector3() : x(0.0), y(0.0), z(0.0) {}

    // Initializes the vector with specific x, y, and z values
    Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    // Initializes the vector using the x, y, z components of a Vector4
    Vector3::Vector3(const Vector4 &v) : x(v.x), y(v.y), z(v.z) {}

    // Adds two vectors component-wise
    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Adds another vector to this vector component-wise
    void Vector3::operator+=(const Vector3 &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }

    // Subtracts another vector from this vector component-wise
    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Negates the vector (inverts the sign of all components)
    Vector3 Vector3::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    // Subtracts another vector from this vector in place
    void Vector3::operator-=(const Vector3 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
    }

    // Multiplies the vector by a scalar value
    Vector3 Vector3::operator*(double scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Calculates the Cross Product (returns a vector perpendicular to both)
    Vector3 Vector3::operator^(const Vector3 &other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    // Calculates the Dot Product (returns a scalar value)
    double Vector3::operator*(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // Multiplies this vector by a scalar in place
    void Vector3::operator*=(double scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
    }
    // Multiplies this vector by another vector component-wise in place
    void Vector3::operator*=(const Vector3 &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
    }

    // Divides the vector by a scalar value
    Vector3 Vector3::operator/(double scalar) const
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Divides this vector by a scalar value in place
    void Vector3::operator/=(double scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
    }

    // Checks if two vectors are not exactly equal
    bool Vector3::operator!=(const Vector3 &other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    // Checks if two vectors are exactly equal
    bool Vector3::operator==(const Vector3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
}