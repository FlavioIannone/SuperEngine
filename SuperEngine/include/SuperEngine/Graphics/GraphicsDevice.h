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

        Microsoft::WRL::ComPtr<ID3D11Buffer> transformationMatrixCB;  // The Transformation matrix constant buffer.
        Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain; // Two way buffer.

        Microsoft::WRL::ComPtr<ID3D11Buffer> cameraMatrixCB;               // The Camera matrix constant buffer. Common to every object.
        Microsoft::WRL::ComPtr<ID3D11Buffer> screenSizeCB;                 // The ScreenSize constant buffer. Common to every object.

        Microsoft::WRL::ComPtr<ID3D11Texture2D> screenTexture;       // The actual texture in the VRAM.
        Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;        // The actual depth texture in the VRAM.
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> screenUAV; // View that lets the GPU read and modify the screen texture.
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> depthUAV;  // View that lets the GPU read and modify the ZBuffer.

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
        bool CreateTransformationMatrixCB();
        bool CreateCameraMatrixCB();
        bool CreateScreenSizeCB();
        void UpdateTransformationMatrixCB(const GPUObjectData &data);
        ID3D11Buffer *GetObjectDataCB() const { return transformationMatrixCB.Get(); }

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