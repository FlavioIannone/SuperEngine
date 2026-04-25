#pragma once
#include <vector>
#include "SuperEngine/Graphics/GraphicTypes.h"
#include "SuperEngine/Components/Camera.h"
#include "SuperEngine/Math/Matrix4x4.h"

namespace SuperEngine
{
    class MeshRenderer;

    class RenderingManager
    {
    private:
        std::vector<MeshRenderer *> renderers;
        Camera *activeCamera = nullptr;

        RenderingManager() = default;
        ~RenderingManager() = default;
        GPUCameraData PrepareCameraData(const Matrix4x4 &view, const Matrix4x4 &proj);
        void UpdateCameraCB();
        void UpdateScreenSizeCB();

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
        // Gets called by the MeshRenderer that needs to be removed from the list when it gets destroyed.
        void RemoveRenderer(MeshRenderer *r);
        void SetActiveCamera(Camera *c) { activeCamera = c; }
        Camera *GetActiveCamera() const { return activeCamera; }
        GPUObjectData PrepareObjectData(const Matrix4x4 &matrix);
        GPUCameraData PrepareCameraData(const Matrix4x4 &view, const Matrix4x4 &proj);
    };
}