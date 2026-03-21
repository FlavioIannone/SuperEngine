#pragma once
#include "Mesh.h"

namespace SuperEngine
{
    class CubeMesh : public Mesh
    {
    public:
        // Constructor
        CubeMesh()
        {
            // Back face
            tris.push_back({Vector4(-1, 1, -1, 1), Vector4(-1, -1, -1, 1), Vector4(1, -1, -1, 1)});
            tris.push_back({Vector4(-1, 1, -1, 1), Vector4(1, 1, -1, 1), Vector4(1, -1, -1, 1)});
            // Front face
            tris.push_back({Vector4(-1, 1, 1, 1), Vector4(-1, -1, 1, 1), Vector4(1, -1, 1, 1)});
            tris.push_back({Vector4(-1, 1, 1, 1), Vector4(1, 1, 1, 1), Vector4(1, -1, 1, 1)});
            // Sides
            // Left
            tris.push_back({Vector4(-1, 1, -1, 1), Vector4(-1, -1, -1, 1), Vector4(-1, -1, 1, 1)});
            tris.push_back({Vector4(-1, 1, -1, 1), Vector4(-1, 1, 1, 1), Vector4(-1, -1, 1, 1)});
            // Top
            tris.push_back({Vector4(-1, 1, -1, 1), Vector4(1, 1, -1, 1), Vector4(1, 1, 1, 1)});
            tris.push_back({Vector4(-1, 1, -1, 1), Vector4(-1, 1, 1, 1), Vector4(1, 1, 1, 1)});
            // Right
            tris.push_back({Vector4(1, 1, -1, 1), Vector4(1, -1, -1, 1), Vector4(1, -1, 1, 1)});
            tris.push_back({Vector4(1, 1, -1, 1), Vector4(1, 1, 1, 1), Vector4(1, -1, 1, 1)});
            // Bottom
            tris.push_back({Vector4(-1, -1, -1, 1), Vector4(1, -1, -1, 1), Vector4(1, -1, 1, 1)});
            tris.push_back({Vector4(-1, -1, -1, 1), Vector4(-1, -1, 1, 1), Vector4(1, -1, 1, 1)});
        }
    };
}