#include "SuperEngine/Components/MeshRenderer.h"
#include "SuperEngine/Engine/Engine.h"
#include "SuperEngine/Engine/AssetManager.h"
#include <iostream>

namespace SuperEngine
{
    void MeshRenderer::SetMesh()
    {
        m_sharedMesh = AssetManager::GetInstance().GetMesh(meshFilepath);

        if (!m_sharedMesh || m_sharedMesh->GetTrianglesCount() == 0)
        {
            std::cout << "Errore: Mesh non valida o vuota!\n";
            return;
        }

        auto device = Engine::GetInstance().GetGraphicsDevice();
        UINT triangleCount = GetSharedMesh()->GetTrianglesCount();

        if (!device->CreateProjectedTriangleBuffer(
                triangleCount,
                m_projectedTriangleBuffer.GetAddressOf(),
                m_projectedTriangleSRV.GetAddressOf(),
                m_projectedTriangleUAV.GetAddressOf()))
        {
            std::cout << "Error creating projected buffer for Renderer.\n";
        }
    }
}