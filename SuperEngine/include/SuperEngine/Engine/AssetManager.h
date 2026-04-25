#pragma once
#include "SuperEngine/Graphics/Mesh/Mesh.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace SuperEngine
{
    class AssetManager
    {
    private:
        AssetManager() = default;
        ~AssetManager() = default;
        const std::string cubeMeshFilepath = "assets/Meshes/CubeMesh.mesh";
        const std::string piramidMeshFilepath = "assets/Meshes/PiramidMesh.mesh";

        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
        std::string LoadMeshFromFile(const std::string &filepath);

    public:
        static AssetManager &GetInstance()
        {
            static AssetManager instance;
            return instance;
        }

        AssetManager(const AssetManager &) = delete;
        void operator=(const AssetManager &) = delete;

        // Returns a cached mesh. On cache miss, a new mesh is created by loading the file located at "filepath",
        // parsing it and inserting the parsed mesh into the cache.
        std::shared_ptr<Mesh> GetMesh(const std::string &filepath);

        // Getters
        const std::string GetCubeMeshFilepath() const { return cubeMeshFilepath; }
        const std::string GetPiramidMeshFilepath() const { return piramidMeshFilepath; }

        void ClearAll();
    };
}