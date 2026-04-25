#include <iostream>
#include "SuperEngine/Graphics/BuiltInShaders.h"
#include "SuperEngine/Engine/Engine.h"

namespace SuperEngine
{
    bool BuiltInShaders::InitShaders()
    {
        geometryPassShader = std::make_unique<ComputeShader>();
        rasterizationPassShader = std::make_unique<ComputeShader>();
        clearScreenShader = std::make_unique<ComputeShader>();

        auto device = Engine::GetInstance().GetGraphicsDevice()->GetDevice();
        if (!geometryPassShader->Load(device, geometryPassShaderPath))
        {
            std::cout << "Error loading geometry pass shader.\n";
            return false;
        }
        if (!rasterizationPassShader->Load(device, rasterizationPassPath))
        {
            std::cout << "Error loading rasterization pass shader.\n";
            return false;
        }

        if (!clearScreenShader->Load(device, clearScreenShaderPath))
        {
            std::cout << "Error loading clear screen shader.\n";
            return false;
        }
        return true;
    }
}