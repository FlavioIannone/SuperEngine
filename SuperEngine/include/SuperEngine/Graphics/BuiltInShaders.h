#pragma once
#include "SuperEngine/Graphics/ComputeShader.h"
#include <xstring>
#include <memory>

namespace SuperEngine
{
    class BuiltInShaders
    {
    private:
        std::unique_ptr<ComputeShader> rasterizationPassShader;
        std::unique_ptr<ComputeShader> geometryPassShader;
        std::unique_ptr<ComputeShader> clearScreenShader;
        std::wstring rasterizationPassPath = L"assets/Shaders/RasterizationPass.hlsl";
        std::wstring geometryPassShaderPath = L"assets/Shaders/GeometryPass.hlsl";
        std::wstring clearScreenShaderPath = L"assets/Shaders/ClearScreenCompute.hlsl";

    public:
        ComputeShader *GetRasterizationPassShader() const { return rasterizationPassShader.get(); }
        ComputeShader *GetGeometryPassShader() const { return geometryPassShader.get(); }
        ComputeShader *GetClearScreenShader() const { return clearScreenShader.get(); }
        bool InitShaders();
    };
}