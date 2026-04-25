#pragma once
#include "SuperEngine/Math/Vector4.h"

namespace SuperEngine
{
    struct Vector3
    {
        double x, y, z;

        Vector3();
        Vector3(double _x, double _y, double _z);
        Vector3(const Vector4 &v);

        // Direction vectors
        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 up;
        static const Vector3 right;
        static const Vector3 forward;

        // --- Operators overload ---

        // Sum
        Vector3 operator+(const Vector3 &other) const;
        void operator+=(const Vector3 &other);

        // Sub
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator-() const;
        void operator-=(const Vector3 &other);

        // Scalar mul
        Vector3 operator*(double scalar) const;
        void operator*=(double scalar);

        // Dot product
        double operator*(const Vector3 &other) const;
        void operator*=(const Vector3 &other);

        // Cross product
        Vector3 operator^(const Vector3 &other) const;

        // Scalar div
        Vector3 operator/(double scalar) const;
        void operator/=(double scalar);

        // Logical operations
        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;
    };

    inline const Vector3 Vector3::zero{0.0, 0.0, 0.0};
    inline const Vector3 Vector3::one{1.0, 1.0, 1.0};
    inline const Vector3 Vector3::up{0.0, 1.0, 0.0};
    inline const Vector3 Vector3::right{1.0, 0.0, 0.0};
    inline const Vector3 Vector3::forward{0.0, 0.0, 1.0};
}