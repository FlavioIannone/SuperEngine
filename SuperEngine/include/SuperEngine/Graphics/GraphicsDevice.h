#pragma once
#include "SuperEngine/Graphics/GraphicTypes.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <SDL.h>
#include <vector>

namespace SuperEngine
{
    class GraphicsDevice
    {
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

        Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain; // Two way buffer.

        Microsoft::WRL::ComPtr<ID3D11Buffer> globalObjectsSB;      // The global Structured Buffer containing transformation matrices. Every renderer uploads its matrix here.
        Microsoft::WRL::ComPtr<ID3D11Buffer> projectedTrianglesSB; // The global Structured Buffer for projected triangles. Threads write here using a calculated global offset.
        Microsoft::WRL::ComPtr<ID3D11Buffer> objectMetadataCB;     // The Constant Buffer containing per-object data (e.g., object index and global write offset).
        Microsoft::WRL::ComPtr<ID3D11Buffer> cameraMatrixCB;       // The Constant Buffer containing the camera's view and projection matrices. Shared across all objects.
        Microsoft::WRL::ComPtr<ID3D11Buffer> screenSizeCB;         // The Constant Buffer containing the screen dimensions. Shared across all objects.

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> globalObjectsSRV;       // The Shader Resource View (SRV) to read the transformation matrices in the compute shader.
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> projectedTrianglesUAV; // The Unordered Access View (UAV) to read/write the projected triangles during the rasterization pass.
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> projectedTrianglesSRV;  // The Shader Resource View (SRV) to read the projected triangles during the rasterization pass.

        Microsoft::WRL::ComPtr<ID3D11Texture2D> screenTexture;       // The actual 2D texture residing in the VRAM representing the final screen output.
        Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;        // The actual 2D texture residing in the VRAM representing the depth buffer (Z-Buffer).
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> screenUAV; // The Unordered Access View (UAV) that allows the compute shader to write pixel colors to the screen.
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> depthUAV;  // The Unordered Access View (UAV) that allows the compute shader to read and update the Z-Buffer.

        const UINT globalObjectsBuffSize = 10000;         // The globalObjectsSB logical size.
        const UINT projectedTrianglesBuffSize = 10000000; // The projectedTrianglesSB logical size.

    public:
        GraphicsDevice();
        ~GraphicsDevice();

        // Initializes a connection between the GPU and the Window.
        bool Initialize(SDL_Window *window, int width, int height);

        // Dispatches the painted image to the window.
        void Present();
        void Resize();

        // Creates a triangles buffer
        bool CreateTriangleBuffer(const std::vector<GPUTriangle> &triangles, ID3D11Buffer **bufferOut, ID3D11ShaderResourceView **srvOut);
        // Creates a projected triangles buffer
        bool CreateProjectedTriangleSB();

        // Buffers' methods
        // Global objects
        bool CreateGlobalObjectsSB();
        ID3D11Buffer *GetGlobalObjectsCB() const { return globalObjectsSB.Get(); }
        void UpdateGlobalObjectsSB(const std::vector<GPUObjectData> &objs);

        // Object metadata
        bool CreateObjectMetadataCB();
        ID3D11Buffer *GetObjectMetadataCB() const { return objectMetadataCB.Get(); }
        void UpdateObjectMetadataCB(const GPUObjectMetadata &objIndex);

        // Camera data
        bool CreateCameraMatrixCB();
        ID3D11Buffer *GetCameraDataCB() const { return cameraMatrixCB.Get(); }
        void UpdateCameraMatrixCB(const GPUCameraData &data);

        // Screen size
        bool CreateScreenSizeCB();
        ID3D11Buffer *GetScreenSizeCB() const { return screenSizeCB.Get(); }
        void UpdateScreenSizeCB(const GPUScreenSize &screen);

        // Getters.
        ID3D11Device *GetDevice() const { return device.Get(); }
        ID3D11DeviceContext *GetContext() const { return context.Get(); }
        ID3D11UnorderedAccessView *GetScreenUAV() const { return screenUAV.Get(); }
        ID3D11UnorderedAccessView *GetZBufferUAV() const { return depthUAV.Get(); }
        ID3D11UnorderedAccessView *GetProjectedTrianglesUAV() const { return projectedTrianglesUAV.Get(); }
        ID3D11ShaderResourceView *GetGlobalObjectsSRV() const { return globalObjectsSRV.Get(); }
        ID3D11ShaderResourceView *GetProjectedTrianglesSRV() const { return projectedTrianglesSRV.Get(); }
    };
}