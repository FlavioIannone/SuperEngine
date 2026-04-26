#pragma once
#include "SuperEngine/Math/Vector4.h"
#include <wrl/client.h>

namespace SuperEngine
{
    // 16 bytes
    struct GPUVertex
    {
        float position[4];
    };

    // 16 bytes
    struct GPUColor
    {
        float channels[4];
    };

    // (3 + 3) * 16 bytes
    struct GPUTriangle
    {
        GPUVertex vertices[3];
        GPUColor colors[3];
    };

    // (16 + 16) * 3 + 4 + 12 (padding) bytes
    struct alignas(16) GPUProjectedTriangle
    {
        GPUVertex vertices[3];
        GPUColor colors[3];
        int isVisible;
    };

    // 16 * 4 bytes
    struct alignas(16) GPUObjectData
    {
        float worldMatrix[16]; // 4x4 matrix
    };

    // 4 + 12 (padding) bytes
    struct alignas(16) GPUObjectIndex
    {
        UINT instanceIndex;
    };

    // (16 + 16) * 4 bytes
    struct alignas(16) GPUCameraData
    {
        float viewMatrix[16];       // 4x4 matrix
        float projectionMatrix[16]; // 4x4 matrix
    };

    // 8 + 8 (padding) bytes
    struct alignas(16) GPUScreenSize
    {
        UINT width;
        UINT height;
    };
}