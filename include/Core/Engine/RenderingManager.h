#pragma once
#include <vector>

namespace SuperEngine
{
    class MeshRenderer;

    class RenderingManager
    {
    private:
        std::vector<MeshRenderer *> renderers;

        RenderingManager() {}
        ~RenderingManager() {}

    public:
        static RenderingManager &GetInstance()
        {
            static RenderingManager instance;
            return instance;
        }

        RenderingManager(const RenderingManager &) = delete;
        RenderingManager &operator=(const RenderingManager &) = delete;

        void Render();
        void AddRenderer(MeshRenderer *r);
        void RemoveRenderer(MeshRenderer *r);
    };
}