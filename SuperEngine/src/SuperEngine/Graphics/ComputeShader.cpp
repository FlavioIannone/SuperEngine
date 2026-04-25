#include "SuperEngine/Graphics/ComputeShader.h"
#include <d3dcompiler.h>
#include <iostream>

namespace SuperEngine
{
    ComputeShader::ComputeShader() {}
    ComputeShader::~ComputeShader() {}

    bool ComputeShader::Load(ID3D11Device *device, const std::wstring &filePath, const std::string &entryPoint)
    {
        // BLOB objects, containers of memory for DirectX.
        Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob = nullptr;
        Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

        // Compiles the HLSL file
        HRESULT hr = D3DCompileFromFile(
            filePath.c_str(),                                // File path .hlsl.
            nullptr,                                         // Macro, none for now.
            D3D_COMPILE_STANDARD_FILE_INCLUDE,               // Include headers.
            entryPoint.c_str(),                              // Entry point of the hlsl shader file.
            "cs_5_0",                                        // Compute Shader v5.0.
            D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG, // Compilation flags.
            0,
            &shaderBlob, // Compiled code container.
            &errorBlob   // Eventual errors container.
        );

        // HDSL Syntax errors handling.
        if (FAILED(hr))
        {
            if (errorBlob)
            {
                std::cerr << "Error compiling shader: "
                          << (char *)errorBlob->GetBufferPointer() << std::endl;
            }
            else
            {
                std::cerr << "Shader file not found." << std::endl;
            }
            return false;
        }

        // Shader creation in the VRAM.
        hr = device->CreateComputeShader(
            shaderBlob->GetBufferPointer(),
            shaderBlob->GetBufferSize(),
            nullptr,
            &shader);

        return SUCCEEDED(hr);
    }

    void ComputeShader::Bind(ID3D11DeviceContext *context, ID3D11ShaderResourceView **srvs, UINT numSrvs, ID3D11Buffer **constantBuffers, UINT numCBs)
    {
        // Bind the shader
        context->CSSetShader(shader.Get(), nullptr, 0);

        // Bind the eventual resources to the shader.
        if (srvs != nullptr && numSrvs > 0)
        {
            context->CSSetShaderResources(0, numSrvs, srvs);
        }
        // Bind the eventual constant buffers to the shader.
        if (constantBuffers != nullptr && numCBs > 0)
        {
            context->CSSetConstantBuffers(0, numCBs, constantBuffers);
        }
    }

    void ComputeShader::Dispatch(ID3D11DeviceContext *context, UINT threadGroupX, UINT threadGroupY, UINT threadGroupZ)
    {
        // Executes the code on the GPU.
        context->Dispatch(threadGroupX, threadGroupY, threadGroupZ);
    }
}