#pragma once
#include "SuperEngine/Components/Component.h"
#include "SuperEngine/Graphics/Mesh/Mesh.h"
#include "SuperEngine/Engine/RenderingManager.h"
#include "SuperEngine/Graphics/GraphicTypes.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <memory>

namespace SuperEngine
{
    class MeshRenderer : public Component
    {
    private:
        std::shared_ptr<Mesh> m_sharedMesh;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_projectedTriangleBuffer;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_projectedTriangleSRV;
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_projectedTriangleUAV;
        std::string meshFilepath;

    public:
        MeshRenderer(const std::string &meshFilepath) : meshFilepath(meshFilepath)
        {
        }

        void Start() override
        {
            RenderingManager::GetInstance().AddRenderer(this);
            SetMesh();
        }

        void OnDestroy() override
        {
            RenderingManager::GetInstance().RemoveRenderer(this);
        }

        // Uploads the mesh data into the GPU VRAM.
        void SetMesh();

        // Getters
        ID3D11ShaderResourceView *GetProjectedTriangleSRV() const { return m_projectedTriangleSRV.Get(); }
        ID3D11UnorderedAccessView *GetProjectedTriangleUAV() const { return m_projectedTriangleUAV.Get(); }
        Mesh *GetSharedMesh() const { return (m_sharedMesh.get()); }
    };
}