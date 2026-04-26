#include "SuperEngine/Graphics/GraphicsDevice.h"
#include "SuperEngine/Graphics/GraphicTypes.h"
#include "SuperEngine/Engine/Engine.h"
#include <SDL_syswm.h>
#include <iostream>
#include <vector>

namespace SuperEngine
{
    GraphicsDevice::GraphicsDevice() {}
    GraphicsDevice::~GraphicsDevice() {}

    bool GraphicsDevice::Initialize(SDL_Window *window, int width, int height)
    {
        // Retrieves the window handle in order to connect the SDL2 window to the image computation logic.
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        if (!SDL_GetWindowWMInfo(window, &wmInfo))
        {
            return false;
        }
        HWND hwnd = wmInfo.info.win.window;

#pragma region SwapChainDesc
        // SWAP CHAIN DEFINITION.
        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferCount = 2;                                // Two buffers, back buffer and front buffer.
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32 bit colors (RGBA).
        scd.BufferDesc.Width = width;
        scd.BufferDesc.Height = height;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Tells the GI the buffer will be used a render target.
        scd.OutputWindow = hwnd;                           // Link to the Window.
        scd.SampleDesc.Count = 1;                          // No Anti-aliasing.
        scd.Windowed = TRUE;                               // Mode: Windowed.
        scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;    // Flip Model, reccomended by microsoft.
#pragma endregion

        // Device creation flags.
        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // Activate GPU error messages, for debug.
#endif

        // DEVICE AND SWAP CHAIN CREATION (PARALLEL OPERATION).
        D3D_FEATURE_LEVEL featureLevel;
        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
            createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION,
            &scd, &swapChain, &device, &featureLevel, &context);

        if (FAILED(hr))
            return false;

#pragma region TexturesDesc
        // Textures description.
        D3D11_TEXTURE2D_DESC screenTextDesc = {};
        screenTextDesc.Width = width;
        screenTextDesc.Height = height;
        screenTextDesc.MipLevels = 1;
        screenTextDesc.ArraySize = 1;
        screenTextDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        screenTextDesc.SampleDesc.Count = 1;
        screenTextDesc.Usage = D3D11_USAGE_DEFAULT;
        screenTextDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

        D3D11_TEXTURE2D_DESC depthTextDesc = {};
        depthTextDesc.Width = width;
        depthTextDesc.Height = height;
        depthTextDesc.MipLevels = 1;
        depthTextDesc.ArraySize = 1;
        depthTextDesc.Format = DXGI_FORMAT_R32_FLOAT;
        depthTextDesc.SampleDesc.Count = 1;
        depthTextDesc.Usage = D3D11_USAGE_DEFAULT;
        depthTextDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
#pragma endregion

        HRESULT hrTex = device->CreateTexture2D(&screenTextDesc, nullptr, &screenTexture);
        if (FAILED(hrTex))
        {
            std::cout << "Cannot create the Screen Texture!\n";
            return false;
        }

        hrTex = device->CreateTexture2D(&depthTextDesc, nullptr, &depthTexture);
        if (FAILED(hrTex))
        {
            std::cout << "Cannot create the Depth Texture!\n";
            return false;
        }

#pragma region UAVsDesc
        // UAV creation.
        D3D11_UNORDERED_ACCESS_VIEW_DESC screenUAVDesc = {};
        screenUAVDesc.Format = screenTextDesc.Format;
        screenUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
        screenUAVDesc.Texture2D.MipSlice = 0;

        D3D11_UNORDERED_ACCESS_VIEW_DESC depthUAVDesc = {};
        depthUAVDesc.Format = depthTextDesc.Format;
        depthUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
        depthUAVDesc.Texture2D.MipSlice = 0;
#pragma endregion

        HRESULT hrUav = device->CreateUnorderedAccessView(screenTexture.Get(), &screenUAVDesc, &screenUAV);
        if (FAILED(hrUav))
        {
            std::cout << "Cannot create the Screen UAV view!\n";
            return false;
        }
        hrUav = device->CreateUnorderedAccessView(depthTexture.Get(), &depthUAVDesc, &depthUAV);
        if (FAILED(hrUav))
        {
            std::cout << "Cannot create the Depth UAV view!\n";
            return false;
        }

        // Creates the constant buffers.
        bool cbsCreationRes = CreateGlobalObjectsCB() && CreateObjectIndexCB() &&
                              CreateCameraMatrixCB() && CreateScreenSizeCB();

        if (!cbsCreationRes)
        {
            std::cout << "Cannot create the Constant buffer!\n";
            return false;
        }

        return true;
    }

    void GraphicsDevice::Present()
    {
        // Back buffer of the swap chain.
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

        // Get the computed result from the GPU.
        context->CopyResource(backBuffer.Get(), screenTexture.Get());

        // Should the vSync be activated
        UINT vSyncFlag = Engine::GetInstance().GetIsVSyncActive();
        // Present the result on screen.
        swapChain->Present(vSyncFlag, 0);
    }

    void GraphicsDevice::Resize()
    {
        int newWidth = Engine::GetInstance().GetWidth(), newHeight = Engine::GetInstance().GetHeight();
        if (!swapChain || !device || newWidth == 0 || newHeight == 0)
            return;

        // Disconnect the UAVs
        ID3D11UnorderedAccessView *nullUAVs[2] = {nullptr, nullptr};
        context->CSSetUnorderedAccessViews(0, 2, nullUAVs, nullptr);

        // Delete the UAVs and Textures
        screenUAV.Reset();
        depthUAV.Reset();
        screenTexture.Reset();
        depthTexture.Reset();

        // Resize the buffers
        HRESULT hr = swapChain->ResizeBuffers(2, newWidth, newHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
        if (FAILED(hr))
        {
            std::cout << "Errore while resizing the swap chain!\n";
            return;
        }

        // Create the new Textures
        D3D11_TEXTURE2D_DESC screenTextDesc = {};
        screenTextDesc.Width = newWidth;
        screenTextDesc.Height = newHeight;
        screenTextDesc.MipLevels = 1;
        screenTextDesc.ArraySize = 1;
        screenTextDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        screenTextDesc.SampleDesc.Count = 1;
        screenTextDesc.Usage = D3D11_USAGE_DEFAULT;
        screenTextDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

        D3D11_TEXTURE2D_DESC depthTextDesc = screenTextDesc;
        depthTextDesc.Format = DXGI_FORMAT_R32_FLOAT;
        depthTextDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;

        device->CreateTexture2D(&screenTextDesc, nullptr, screenTexture.GetAddressOf());
        device->CreateTexture2D(&depthTextDesc, nullptr, depthTexture.GetAddressOf());

        // Create the new uavs
        D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = screenTextDesc.Format;
        uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

        device->CreateUnorderedAccessView(screenTexture.Get(), &uavDesc, screenUAV.GetAddressOf());

        uavDesc.Format = depthTextDesc.Format;
        device->CreateUnorderedAccessView(depthTexture.Get(), &uavDesc, depthUAV.GetAddressOf());
    }

    bool GraphicsDevice::CreateTriangleBuffer(const std::vector<GPUTriangle> &triangles, ID3D11Buffer **bufferOut, ID3D11ShaderResourceView **srvOut)
    {
        if (triangles.empty())
            return false;

        // Description of the triangles buffer
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(GPUTriangle) * triangles.size(); // Total size, in bytes
        bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;             // Will be used as a shader resource
        bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;  // It is a structured buffer
        bufferDesc.StructureByteStride = sizeof(GPUTriangle);          // Size of a single buffer element

        // Preparing the data to inject into the buffer
        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = triangles.data(); // Pointer to the vector

        // Create the physical buffer
        HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, bufferOut);
        if (FAILED(hr))
            return false;

        // Creating the View, to able the shader to see the buffer
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = DXGI_FORMAT_UNKNOWN; // Let the shader see the raw data
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        srvDesc.Buffer.FirstElement = 0;
        srvDesc.Buffer.NumElements = triangles.size();

        // Binding the View to the buffer
        hr = device->CreateShaderResourceView(*bufferOut, &srvDesc, srvOut);

        return SUCCEEDED(hr);
    }
    bool GraphicsDevice::CreateProjectedTriangleBuffer(UINT triangleCount, ID3D11Buffer **bufferOut, ID3D11ShaderResourceView **srvOut, ID3D11UnorderedAccessView **uavOut)
    {
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_DEFAULT; // GPU Reads and Writes, CPU no
        bd.ByteWidth = sizeof(GPUProjectedTriangle) * triangleCount;
        bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        bd.CPUAccessFlags = 0;
        bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bd.StructureByteStride = sizeof(GPUProjectedTriangle);

        HRESULT hr = device->CreateBuffer(&bd, nullptr, bufferOut);
        if (FAILED(hr))
            return false;
        // Shader Resource View, Let's the GPU Read, but not write, for the pass 2
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = DXGI_FORMAT_UNKNOWN; // Let the shader see the raw data
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        srvDesc.Buffer.FirstElement = 0;
        srvDesc.Buffer.NumElements = triangleCount;

        hr = device->CreateShaderResourceView(*bufferOut, &srvDesc, srvOut);
        if (FAILED(hr))
            return false;

        // Unordered Access View, Let's the GPU Read and Write, for the pass 1
        D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = DXGI_FORMAT_UNKNOWN;
        uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
        uavDesc.Buffer.FirstElement = 0;
        uavDesc.Buffer.NumElements = triangleCount;

        hr = device->CreateUnorderedAccessView(*bufferOut, &uavDesc, uavOut);
        if (FAILED(hr))
            return false;
        return true;
    }

    bool GraphicsDevice::CreateGlobalObjectsCB()
    {
        D3D11_BUFFER_DESC sbDesc = {};
        sbDesc.ByteWidth = sizeof(Matrix4x4) * globalObjectsBuffSize; // Space for globalObjectsBuffSize matrices
        sbDesc.Usage = D3D11_USAGE_DYNAMIC;                           // The CPU will update this buffer every frame
        sbDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;                // Will be read by a SRV
        sbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;               // CPU can write
        sbDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;     // This is a StructuredBuffer
        sbDesc.StructureByteStride = sizeof(Matrix4x4);               // Size of a single structure

        // Create the buffer
        HRESULT hr = device->CreateBuffer(&sbDesc, nullptr, globalObjectsCB.GetAddressOf());
        if (FAILED(hr))
        {
            std::cout << "Error while creating the GlobalObjects buffer.\n";
            return false;
        }

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        srvDesc.Buffer.FirstElement = 0;
        srvDesc.Buffer.NumElements = globalObjectsBuffSize;
        hr = device->CreateShaderResourceView(globalObjectsCB.Get(), &srvDesc, globalObjectsSRV.GetAddressOf());

        return true;
    }
    bool GraphicsDevice::CreateCameraMatrixCB()
    {
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_DYNAMIC;       // Updated by the CPU, read by the GPU.
        bd.ByteWidth = sizeof(GPUCameraData); // Has to be a multiple of 16, GPU alignation rules.
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU needs the access to write.
        bd.MiscFlags = 0;
        bd.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&bd, nullptr, &cameraMatrixCB);
        return SUCCEEDED(hr);
    }
    bool GraphicsDevice::CreateScreenSizeCB()
    {
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_DYNAMIC;       // Updated by the CPU, read by the GPU.
        bd.ByteWidth = sizeof(GPUScreenSize); // Has to be a multiple of 16, GPU alignation rules.
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU needs the access to write.
        bd.MiscFlags = 0;
        bd.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&bd, nullptr, &screenSizeCB);
        return SUCCEEDED(hr);
    }
    bool GraphicsDevice::CreateObjectIndexCB()
    {
        D3D11_BUFFER_DESC idxDesc = {};
        idxDesc.Usage = D3D11_USAGE_DYNAMIC;
        idxDesc.ByteWidth = sizeof(GPUObjectIndex);
        idxDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        idxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        idxDesc.MiscFlags = 0;
        idxDesc.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&idxDesc, nullptr, objectIndexCB.GetAddressOf());
        if (FAILED(hr))
        {
            std::cout << "Errore while creating the ObjectIndexCB!\n";
            return false;
        }
        return true;
    }

    void GraphicsDevice::UpdateCameraMatrixCB(const GPUCameraData &data)
    {
        if (!cameraMatrixCB)
            return;

        D3D11_MAPPED_SUBRESOURCE mappedResource;

        // Maps the data in the buffer, this also locks the resource. D3D11_MAP_WRITE_DISCARD tells the GPU to delete the previous data.
        HRESULT hr = context->Map(cameraMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if (SUCCEEDED(hr))
        {
            // Copy the data into the VRAM buffer.
            memcpy(mappedResource.pData, &data, sizeof(GPUCameraData));

            // Unlock the memory
            context->Unmap(cameraMatrixCB.Get(), 0);
        }
    }
    void GraphicsDevice::UpdateScreenSizeCB(const GPUScreenSize &size)
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;

        // Maps the data in the buffer, this also locks the resource. D3D11_MAP_WRITE_DISCARD tells the GPU to delete the previous data.
        HRESULT hr = context->Map(screenSizeCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if (SUCCEEDED(hr))
        {
            // Copy the data into the VRAM buffer.
            memcpy(mappedResource.pData, &size, sizeof(GPUScreenSize));

            // Unlock the memory
            context->Unmap(screenSizeCB.Get(), 0);
        }
    }
    void GraphicsDevice::UpdateGlobalObjectsCB(const std::vector<GPUObjectData> &objs)
    {
        if (objs.empty())
            return;

        D3D11_MAPPED_SUBRESOURCE mapped;
        context->Map(GetGlobalObjectsCB(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped); // Lock the buffer
        memcpy(mapped.pData, objs.data(), sizeof(GPUObjectData) * objs.size());     // Copy the data into the VRAM
        context->Unmap(GetGlobalObjectsCB(), 0);
    }
    void GraphicsDevice::UpdateObjectIndexCB(UINT instanceIndex)
    {
        if (!objectIndexCB || !context)
            return;

        D3D11_MAPPED_SUBRESOURCE mapped;

        HRESULT hr = context->Map(objectIndexCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

        if (SUCCEEDED(hr))
        {
            GPUObjectIndex data = {};
            data.instanceIndex = instanceIndex;
            memcpy(mapped.pData, &data, sizeof(GPUObjectIndex));

            context->Unmap(objectIndexCB.Get(), 0);
        }
    }
}