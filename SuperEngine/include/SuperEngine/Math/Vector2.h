#pragma once

namespace SuperEngine
{
    struct Vector2
    {
        double x, y;

        Vector2();
        Vector2(double _x, double _y);

        // Direction vectors
        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 up;
        static const Vector2 right;

        // --- Operators overload ---

        // Addition
        Vector2 operator+(const Vector2 &other) const;
        void operator+=(const Vector2 &other);

        // Subtraction and Negation
        Vector2 operator-(const Vector2 &other) const;
        Vector2 operator-() const;
        void operator-=(const Vector2 &other);

        // Scalar Multiplication
        Vector2 operator*(double scalar) const;
        void operator*=(double scalar);

        // Dot Product and Component-wise Multiplication
        double operator*(const Vector2 &other) const;
        void operator*=(const Vector2 &other);

        // Scalar Division
        Vector2 operator/(double scalar) const;
        void operator/=(double scalar);

        // Logical Operators
        bool operator!=(const Vector2 &other) const;
        bool operator==(const Vector2 &other) const;
    };

    inline const Vector2 Vector2::zero{0.0, 0.0};
    inline const Vector2 Vector2::one{1.0, 1.0};
    inline const Vector2 Vector2::up{0.0, 1.0};
    inline const Vector2 Vector2::right{1.0, 0.0};
}