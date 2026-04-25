#include "SuperEngine/Engine/AssetManager.h"
#include "SuperEngine/Engine/Engine.h"
#include "SuperEngine/Graphics/GraphicsDevice.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace SuperEngine
{
    std::shared_ptr<Mesh> AssetManager::GetMesh(const std::string &filepath)
    {

        auto it = m_meshes.find(filepath);
        if (it != m_meshes.end())
        {
            return it->second;
        }

        std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>();
        Mesh *raw_ptr = newMesh.get();
        std::string meshString = LoadMeshFromFile(filepath);
        raw_ptr->ParseMesh(meshString);
        raw_ptr->UploadMeshToGPU();

        m_meshes[filepath] = newMesh;

        return newMesh;
    }

    std::string AssetManager::LoadMeshFromFile(const std::string &filepath)
    {
        std::ifstream file(filepath, std::ios::in | std::ios::binary);

        if (!file)
        {
            std::cout << "Error: Cannot open file '" + filepath + "'\n";
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void AssetManager::ClearAll()
    {
        m_meshes.clear();
    }
}