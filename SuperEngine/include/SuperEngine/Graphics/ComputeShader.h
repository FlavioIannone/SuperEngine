#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <string>

namespace SuperEngine
{
    class ComputeShader
    {
    public:
        ComputeShader();
        ~ComputeShader();

        // Loads a HLSL file, compiles it and creates the shader. entryPoint is the name of the HLSL file entry point.
        bool Load(ID3D11Device *device, const std::wstring &filePath, const std::string &entryPoint = "CSMain");

        // Binds this shader to the pipeline.
        void Bind(ID3D11DeviceContext *context, ID3D11ShaderResourceView **srvs = nullptr, UINT numSrvs = 0, ID3D11Buffer **constantBuffers = nullptr, UINT numCBs = 0);

        // Dispatches (threadGroupX * threadGroupY * threadGroupZ) parallel work groups
        void Dispatch(ID3D11DeviceContext *context, UINT threadGroupX, UINT threadGroupY, UINT threadGroupZ);

    private:
        // Object representing the compiled shader in the VRAM
        Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader;
    };
}