#include "Core/Engine/RenderingManager.h"
#include <algorithm>
#include <SDL.h>
#include "Core/Core.h"
#include <iostream>

namespace SuperEngine
{
    void RenderingManager::Render()
    {

        SDL_Renderer *sdlRenderer = Engine::GetInstance().GetRenderer();
        Camera *mainCam = Camera::GetMainCamera();

        if (!sdlRenderer || !mainCam)
            return;

        const Matrix4x4 &projMatrix = mainCam->CalculateProjectionMatrix();

        SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

        float fWidth = static_cast<float>(Engine::GetInstance().GetWidth());
        float fHeight = static_cast<float>(Engine::GetInstance().GetHeight());

        for (MeshRenderer *r : renderers)
        {
            if (!r->IsEnabled())
                continue;

            Transform *transform = r->GetGameObject()->GetTransform();

            for (const auto &tri : r->GetMesh().GetTriangles())
            {
                Triangle projectedTri;

                for (int i = 0; i < 3; i++)
                {
                    Vector4 v = tri.vertices[i];

                    // Translate vertex
                    if (transform)
                    {
                        v.x += transform->position.x;
                        v.y += transform->position.y;
                        v.z += transform->position.z;
                    }

                    // Apply projection matrix to the vertex
                    projectedTri.vertices[i] = Matrix4x4::MultiplyVector4(projMatrix, v);

                    // Perspective divide
                    if (projectedTri.vertices[i].w != 0.0f)
                    {
                        projectedTri.vertices[i].x /= projectedTri.vertices[i].w;
                        projectedTri.vertices[i].y /= projectedTri.vertices[i].w;
                    }

                    // Obtain on screen position
                    projectedTri.vertices[i].x = (projectedTri.vertices[i].x + 1.0f) * 0.5f * fWidth;
                    projectedTri.vertices[i].y = (1.0f - projectedTri.vertices[i].y) * 0.5f * fHeight;
                }
                // Render triangle wireframe
                SDL_RenderDrawLineF(sdlRenderer, projectedTri.vertices[0].x, projectedTri.vertices[0].y, projectedTri.vertices[1].x, projectedTri.vertices[1].y);
                SDL_RenderDrawLineF(sdlRenderer, projectedTri.vertices[1].x, projectedTri.vertices[1].y, projectedTri.vertices[2].x, projectedTri.vertices[2].y);
                SDL_RenderDrawLineF(sdlRenderer, projectedTri.vertices[2].x, projectedTri.vertices[2].y, projectedTri.vertices[0].x, projectedTri.vertices[0].y);
            }
        }
    }

    void RenderingManager::AddRenderer(MeshRenderer *r)
    {
        renderers.push_back(r);
    }

    // Gets called by the MeshRenderer that needs to be removed from the list when it gets destroyed.
    void RenderingManager::RemoveRenderer(MeshRenderer *r)
    {
        renderers.erase(std::remove(renderers.begin(), renderers.end(), r), renderers.end());
    }
}