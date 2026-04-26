#include "SuperEngine/Engine/RenderingManager.h"
#include <algorithm>
#include <SDL.h>
#include "SuperEngine/SuperEngine.h"
#include <iostream>

namespace SuperEngine
{
    void RenderingManager::Render()
    {
        auto graphicsDevice = Engine::GetInstance().GetGraphicsDevice();
        auto context = graphicsDevice->GetContext();

        // Shaders
        auto geometryPassShader = Engine::GetInstance().GetBuiltInShaders()->GetGeometryPassShader();
        auto rasterizationPassShader = Engine::GetInstance().GetBuiltInShaders()->GetRasterizationPassShader();
        auto clearScreenShader = Engine::GetInstance().GetBuiltInShaders()->GetClearScreenShader();

        // Dispath values
        UINT dispatchX = static_cast<UINT>(Engine::GetInstance().GetWidth() / 8);
        UINT dispatchY = static_cast<UINT>(Engine::GetInstance().GetHeight() / 8);

        clearScreenShader->Bind(context);
        clearScreenShader->Dispatch(context, dispatchX, dispatchY, 1);

        // View setup
        auto screenUAV = graphicsDevice->GetScreenUAV();
        auto zBufferUAV = graphicsDevice->GetZBufferUAV();

        // Loads the camera data into the constant buffer
        UpdateCameraCB();
        // Loads the screen size data into the constant buffer
        UpdateScreenSizeCB();
        // Loads the transformation data into the constant buffer
        UpdateObjectDataSB();

        // Bind the globalObjects srv (t1)
        ID3D11ShaderResourceView *transformSRVs[1] = {graphicsDevice->GetGlobalObjectsSRV()};
        context->CSSetShaderResources(1, 1, transformSRVs);

        UINT objectIndex = 0;
        UINT globalOffset = 0;
        for (MeshRenderer *r : renderers)
        {
            if (!r->IsEnabled())
                continue;

            UINT trianglesCount = r->GetSharedMesh()->GetTrianglesCount(); // Number of triangles in this mesh
            UINT gpuDispatchGroups = (trianglesCount + 63) / 64;           // Numbers of thread groups

            // Object metadata
            GPUObjectMetadata objMetadata = {};
            objMetadata.objectIndex = objectIndex;
            objMetadata.globalOffset = globalOffset;
            graphicsDevice->UpdateObjectMetadataCB(objMetadata);

            // GEOMETRY PASS
            geometryPassShader->Bind(context);
            // Geometry cbs
            ID3D11Buffer *cbs[3] = {
                graphicsDevice->GetCameraDataCB(),    // b0
                graphicsDevice->GetScreenSizeCB(),    // b1
                graphicsDevice->GetObjectMetadataCB() // b2
            };
            context->CSSetConstantBuffers(0, sizeof(cbs) / sizeof(ID3D11Buffer *), cbs);
            // Geometry srvs
            ID3D11ShaderResourceView *srvs[1] = {r->GetSharedMesh()->GetTrianglesSRV()};
            context->CSSetShaderResources(0, sizeof(srvs) / sizeof(ID3D11ShaderResourceView *), srvs); // t0
            // Geometry uavs
            ID3D11UnorderedAccessView *uavs[1] = {graphicsDevice->GetProjectedTrianglesUAV()};
            context->CSSetUnorderedAccessViews(0, sizeof(uavs) / sizeof(ID3D11UnorderedAccessView *), uavs, nullptr); // u0
            geometryPassShader->Dispatch(context, gpuDispatchGroups, 1, 1);

            objectIndex++;
            globalOffset += trianglesCount;
        }

        // Bind the rasterization shader pass
        rasterizationPassShader->Bind(context);
        // Rasterization cbs
        ID3D11Buffer *cbs[1] = {graphicsDevice->GetScreenSizeCB()};
        context->CSSetConstantBuffers(0, sizeof(cbs) / sizeof(ID3D11Buffer *), cbs);

        // Rasterization uavs
        ID3D11UnorderedAccessView *uavs[2] = {graphicsDevice->GetScreenUAV(), graphicsDevice->GetZBufferUAV()};
        context->CSSetUnorderedAccessViews(0, sizeof(uavs) / sizeof(ID3D11UnorderedAccessView *), uavs, nullptr);

        // Rasterization srvs
        ID3D11ShaderResourceView *srvs[1] = {graphicsDevice->GetProjectedTrianglesSRV()};
        context->CSSetShaderResources(0, sizeof(srvs) / sizeof(ID3D11ShaderResourceView *), srvs);
        UINT dispathGroups = (globalOffset + (globalOffset - 1)) / 64;
        rasterizationPassShader->Dispatch(context, dispatchX, 1, 1);
    }
    void RenderingManager::AddRenderer(MeshRenderer *r)
    {
        renderers.push_back(r);
    }

    void RenderingManager::RemoveRenderer(MeshRenderer *r)
    {
        renderers.erase(std::remove(renderers.begin(), renderers.end(), r), renderers.end());
    }

    GPUObjectData RenderingManager::PrepareObjectData(const Matrix4x4 &matrix)
    {
        GPUObjectData data;
        Matrix4x4 mat = matrix;
        // Flattens the matrix
        data.worldMatrix[0] = (Matrix4x4::GetFlattenMatrix<float>(mat))[0];
        data.worldMatrix[1] = (Matrix4x4::GetFlattenMatrix<float>(mat))[1];
        data.worldMatrix[2] = (Matrix4x4::GetFlattenMatrix<float>(mat))[2];
        data.worldMatrix[3] = (Matrix4x4::GetFlattenMatrix<float>(mat))[3];
        data.worldMatrix[4] = (Matrix4x4::GetFlattenMatrix<float>(mat))[4];
        data.worldMatrix[5] = (Matrix4x4::GetFlattenMatrix<float>(mat))[5];
        data.worldMatrix[6] = (Matrix4x4::GetFlattenMatrix<float>(mat))[6];
        data.worldMatrix[7] = (Matrix4x4::GetFlattenMatrix<float>(mat))[7];
        data.worldMatrix[8] = (Matrix4x4::GetFlattenMatrix<float>(mat))[8];
        data.worldMatrix[9] = (Matrix4x4::GetFlattenMatrix<float>(mat))[9];
        data.worldMatrix[10] = (Matrix4x4::GetFlattenMatrix<float>(mat))[10];
        data.worldMatrix[11] = (Matrix4x4::GetFlattenMatrix<float>(mat))[11];
        data.worldMatrix[12] = (Matrix4x4::GetFlattenMatrix<float>(mat))[12];
        data.worldMatrix[13] = (Matrix4x4::GetFlattenMatrix<float>(mat))[13];
        data.worldMatrix[14] = (Matrix4x4::GetFlattenMatrix<float>(mat))[14];
        data.worldMatrix[15] = (Matrix4x4::GetFlattenMatrix<float>(mat))[15];

        return data;
    }
    GPUCameraData RenderingManager::PrepareCameraData(const Matrix4x4 &view, const Matrix4x4 &proj)
    {
        GPUCameraData data;
        Matrix4x4 viewWork = view;
        Matrix4x4 projWork = proj;
        // Flattens the matrices
        // View Matrix
        data.viewMatrix[0] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[0];
        data.viewMatrix[1] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[1];
        data.viewMatrix[2] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[2];
        data.viewMatrix[3] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[3];
        data.viewMatrix[4] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[4];
        data.viewMatrix[5] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[5];
        data.viewMatrix[6] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[6];
        data.viewMatrix[7] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[7];
        data.viewMatrix[8] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[8];
        data.viewMatrix[9] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[9];
        data.viewMatrix[10] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[10];
        data.viewMatrix[11] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[11];
        data.viewMatrix[12] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[12];
        data.viewMatrix[13] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[13];
        data.viewMatrix[14] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[14];
        data.viewMatrix[15] = (Matrix4x4::GetFlattenMatrix<float>(viewWork))[15];

        // Projection matrix
        data.projectionMatrix[0] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[0];
        data.projectionMatrix[1] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[1];
        data.projectionMatrix[2] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[2];
        data.projectionMatrix[3] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[3];
        data.projectionMatrix[4] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[4];
        data.projectionMatrix[5] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[5];
        data.projectionMatrix[6] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[6];
        data.projectionMatrix[7] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[7];
        data.projectionMatrix[8] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[8];
        data.projectionMatrix[9] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[9];
        data.projectionMatrix[10] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[10];
        data.projectionMatrix[11] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[11];
        data.projectionMatrix[12] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[12];
        data.projectionMatrix[13] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[13];
        data.projectionMatrix[14] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[14];
        data.projectionMatrix[15] = (Matrix4x4::GetFlattenMatrix<float>(projWork))[15];

        return data;
    }

    void RenderingManager::UpdateCameraCB()
    {
        auto graphicsDevice = Engine::GetInstance().GetGraphicsDevice();
        auto cam = GetActiveCamera();
        if (!cam)
        {
            cam = Camera::GetMainCamera();
        }
        // Loads the camera view matrix and projection into the constant buffer
        GPUCameraData cm_objData = PrepareCameraData(cam->CalculateViewMatrix(), cam->CalculateProjectionMatrix());
        graphicsDevice->UpdateCameraMatrixCB(cm_objData);
    }
    void RenderingManager::UpdateScreenSizeCB()
    {
        auto graphicsDevice = Engine::GetInstance().GetGraphicsDevice();

        // Loads the screen size data into the constant buffer
        GPUScreenSize sz_objData;
        sz_objData.width = static_cast<UINT>(Engine::GetInstance().GetWidth());
        sz_objData.height = static_cast<UINT>(Engine::GetInstance().GetHeight());
        graphicsDevice->UpdateScreenSizeCB(sz_objData);
    }
    void RenderingManager::UpdateObjectDataSB()
    {
        auto graphicsDevice = Engine::GetInstance().GetGraphicsDevice();
        auto context = graphicsDevice->GetContext();
        // Prepares the bucket with all the matrices of the active renderers in the scene
        std::vector<GPUObjectData> matrices;
        matrices.reserve(renderers.size());

        for (auto r : renderers)
        {
            if (!r->IsEnabled())
                continue;
            Matrix4x4 m = r->GetGameObject()->GetTransform()->CalculateTransformationMatrix();
            matrices.push_back(PrepareObjectData(m));
        }

        // Upload the matrices bucket into the VRAM
        graphicsDevice->UpdateGlobalObjectsSB(matrices);
    }
}