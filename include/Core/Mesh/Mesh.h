#pragma once
#include "../Math/Triangle.h"
#include <vector>

namespace SuperEngine
{
    class Mesh
    {
    protected:
        std::vector<Triangle> tris;

    public:
        // Methods
        const std::vector<Triangle> &GetTriangles() const
        {
            return tris;
        }
    };
}