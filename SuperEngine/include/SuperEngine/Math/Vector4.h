#pragma once

namespace SuperEngine
{
    struct Vector4
    {
        double x, y, z, w;

        Vector4();
        Vector4(double _x, double _y, double _z, double _w);

        // Direction vectors
        static const Vector4 zero;
        static const Vector4 one;
        static const Vector4 up;
        static const Vector4 right;
        static const Vector4 forward;

        // --- Operators overload ---

        // Addition
        Vector4 operator+(const Vector4 &other) const;
        void operator+=(const Vector4 &other);

        // Subtraction and Negation
        Vector4 operator-(const Vector4 &other) const;
        Vector4 operator-() const;
        void operator-=(const Vector4 &other);

        // Scalar Multiplication
        Vector4 operator*(double scalar) const;
        void operator*=(double scalar);

        // Dot Product and Component-wise Multiplication
        double operator*(const Vector4 &other) const;
        void operator*=(const Vector4 &other);

        // Scalar Division
        Vector4 operator/(double scalar) const;
        void operator/=(double scalar);

        // Logical Operators
        bool operator!=(const Vector4 &other) const;
        bool operator==(const Vector4 &other) const;
    };

    inline const Vector4 Vector4::zero{0.0, 0.0, 0.0, 0.0};
    inline const Vector4 Vector4::one{1.0, 1.0, 1.0, 1.0};
    inline const Vector4 Vector4::up{0.0, 1.0, 0.0, 0.0};
    inline const Vector4 Vector4::right{1.0, 0.0, 0.0, 0.0};
    inline const Vector4 Vector4::forward{0.0, 0.0, 1.0, 0.0};
}