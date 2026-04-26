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

        Microsoft::WRL::ComPtr<ID3D11Buffer> objectIndexCB;                // Buffer containing the indeces of every renderer's matrix in the globalObjectsCB.
        Microsoft::WRL::ComPtr<ID3D11Buffer> cameraMatrixCB;               // The Camera matrix constant buffer. Common to every object.
        Microsoft::WRL::ComPtr<ID3D11Buffer> screenSizeCB;                 // The ScreenSize constant buffer. Common to every object.
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> globalObjectsSRV; // The globalObjectsCB SRV.
        Microsoft::WRL::ComPtr<ID3D11Buffer> globalObjectsCB;      // The global Structured Buffer containing transformation matrices. Every renderer uploads its matrix here.

        Microsoft::WRL::ComPtr<ID3D11Texture2D> screenTexture;       // The actual texture in the VRAM.
        Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;        // The actual depth texture in the VRAM.
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> screenUAV; // View that lets the GPU read and modify the screen texture.
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> depthUAV;  // View that lets the GPU read and modify the ZBuffer.

        const UINT globalObjectsBuffSize = 10000; // The globalObjectsCB logical size.

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
        bool CreateProjectedTriangleBuffer(UINT triangleCount, ID3D11Buffer **bufferOut, ID3D11ShaderResourceView **srvOut, ID3D11UnorderedAccessView **uavOut);

        // Constant buffer methods
        bool CreateGlobalObjectsCB();
        bool CreateObjectIndexCB();
        bool CreateCameraMatrixCB();
        bool CreateScreenSizeCB();

        ID3D11Buffer *GetGlobalObjectsCB() const { return globalObjectsCB.Get(); }
        ID3D11ShaderResourceView *GetGlobalObjectsSRV() const { return globalObjectsSRV.Get(); }
        void UpdateGlobalObjectsCB(const std::vector<GPUObjectData> &objs);

        ID3D11Buffer *GetObjectIndexCB() const { return objectIndexCB.Get(); }
        void UpdateObjectIndexCB(UINT instanceIndex);

        ID3D11Buffer *GetCameraDataCB() const { return cameraMatrixCB.Get(); }
        void UpdateCameraMatrixCB(const GPUCameraData &data);

        ID3D11Buffer *GetScreenSizeCB() const { return screenSizeCB.Get(); }
        void UpdateScreenSizeCB(const GPUScreenSize &screen);

        // Getters.
        ID3D11Device *GetDevice() const { return device.Get(); }
        ID3D11DeviceContext *GetContext() const { return context.Get(); }
        ID3D11UnorderedAccessView *GetScreenUAV() const { return screenUAV.Get(); }
        ID3D11UnorderedAccessView *GetZBufferUAV() const { return depthUAV.Get(); }
    };
}