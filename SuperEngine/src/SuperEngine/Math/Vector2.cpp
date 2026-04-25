#include <cmath>
#include "SuperEngine/Math/Vector2.h"

namespace SuperEngine
{
    // Initializes the vector to (0.0, 0.0)
    Vector2::Vector2() : x(0.0), y(0.0) {}

    // Initializes the vector with specific x and y values
    Vector2::Vector2(double _x, double _y) : x(_x), y(_y) {}

    // Adds two vectors component-wise
    Vector2 Vector2::operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    // Adds another vector to this vector component-wise in place
    void Vector2::operator+=(const Vector2 &other)
    {
        this->x += other.x;
        this->y += other.y;
    }

    // Subtracts another vector from this vector component-wise
    Vector2 Vector2::operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    // Negates the vector (inverts the sign of both components)
    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    // Subtracts another vector from this vector in place
    void Vector2::operator-=(const Vector2 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
    }

    // Multiplies the vector by a scalar value
    Vector2 Vector2::operator*(double scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    // Multiplies this vector by a scalar value in place
    void Vector2::operator*=(double scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
    }

    // Calculates the Dot Product (returns a scalar value)
    double Vector2::operator*(const Vector2 &other) const
    {
        return x * other.x + y * other.y;
    }

    // Multiplies this vector by another vector component-wise in place
    void Vector2::operator*=(const Vector2 &other)
    {
        this->x *= other.x;
        this->y *= other.y;
    }

    // Divides the vector by a scalar value
    Vector2 Vector2::operator/(double scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    // Divides this vector by a scalar value in place
    void Vector2::operator/=(double scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
    }

    // Checks if two vectors are not exactly equal
    bool Vector2::operator!=(const Vector2 &other) const
    {
        return x != other.x || y != other.y;
    }

    // Checks if two vectors are exactly equal
    bool Vector2::operator==(const Vector2 &other) const
    {
        return x == other.x && y == other.y;
    }
}