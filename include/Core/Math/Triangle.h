#pragma once
#include <vector>
#include "Vector4.h"

namespace SuperEngine
{
    struct Triangle
    {
        Vector4 vertices[3];

        Triangle()
        {
            vertices[0] = Vector4::zero;
            vertices[1] = Vector4::zero;
            vertices[2] = Vector4::zero;
        }

        Triangle(const Vector4 &p1, const Vector4 &p2, const Vector4 &p3)
        {
            vertices[0] = p1;
            vertices[1] = p2;
            vertices[2] = p3;
        }
    };
}