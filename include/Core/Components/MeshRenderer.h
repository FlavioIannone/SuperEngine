#pragma once
#include "Component.h"
#include "../Mesh/Mesh.h"
#include "Core/Engine/RenderingManager.h"

namespace SuperEngine
{
    class MeshRenderer : public Component
    {
    private:
        Mesh mesh;

    public:
        MeshRenderer(Mesh m) : mesh(m) {}

        void Start() override
        {
            RenderingManager::GetInstance().AddRenderer(this);
        }

        void OnDestroy() override
        {
            RenderingManager::GetInstance().RemoveRenderer(this);
        }

        const Mesh &GetMesh() const { return mesh; }
    };
}