#pragma once
#include "SuperEngine/Graphics/GraphicTypes.h"
#include <vector>
#include <string>
#include <wrl/client.h>
#include <d3d11.h>

namespace SuperEngine
{
    class Mesh
    {
    protected:
        std::vector<GPUTriangle> tris;
        UINT m_triangleCount = 0;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_triangleBuffer = nullptr;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_triangleSRV = nullptr;

    public:
        // Methods
        const std::vector<GPUTriangle> &GetTriangles() const
        {
            return tris;
        }

        const UINT GetTrianglesCount() const { return m_triangleCount; }
        ID3D11ShaderResourceView *GetTrianglesSRV() const { return m_triangleSRV.Get(); }

        bool ParseMesh(const std::string &meshString);
        void UploadMeshToGPU();
    };
}