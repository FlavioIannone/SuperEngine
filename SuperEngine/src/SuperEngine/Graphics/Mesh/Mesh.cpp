#include "SuperEngine/Graphics/Mesh/Mesh.h"
#include "SuperEngine/Engine/Engine.h"
#include <iostream>
#include <sstream>

namespace SuperEngine
{

    bool Mesh::ParseMesh(const std::string &meshString)
    {
        try
        {
            std::stringstream ss(meshString);
            std::string line;
            int c = 0;
            while (std::getline(ss, line))
            {
                c++;
                if (line.empty())
                    continue;
                GPUTriangle t;
                std::stringstream lineStream(line);
                for (int i = 0; i < 3; i++)
                {
                    float vPos;
                    float cChannel;

                    // Get the position of the current vertex
                    lineStream >> vPos;
                    t.vertices[i].position[0] = vPos;
                    lineStream >> vPos;
                    t.vertices[i].position[1] = vPos;
                    lineStream >> vPos;
                    t.vertices[i].position[2] = vPos;
                    lineStream >> vPos;
                    t.vertices[i].position[3] = vPos;
                    // Get the color of the current vertex
                    lineStream >> cChannel;
                    t.colors[i].channels[0] = cChannel;
                    lineStream >> cChannel;
                    t.colors[i].channels[1] = cChannel;
                    lineStream >> cChannel;
                    t.colors[i].channels[2] = cChannel;
                    lineStream >> cChannel;
                    t.colors[i].channels[3] = cChannel;
                }
                // Write on the actual mesh
                if (!lineStream.fail())
                {
                    tris.push_back(t);
                    m_triangleCount++;
                }
                else
                {
                    std::cout << "[Warning]: The " << c << " row of the mesh will be ignored.\n";
                }
            }
        }
        catch (...)
        {
            // Catch-all for unexpected exceptions
            std::cout << "An error occurred while parsing the mesh.\n";
            return false;
        }
        return true;
    }

    void Mesh::UploadMeshToGPU()
    {
        auto device = Engine::GetInstance().GetGraphicsDevice();
        if (!device)
            return;
        const auto &gpuTriangles = GetTriangles();
        m_triangleCount = static_cast<UINT>(gpuTriangles.size());
        if (m_triangleCount == 0)
            return;

        if (!device->CreateTriangleBuffer(gpuTriangles, m_triangleBuffer.GetAddressOf(), m_triangleSRV.GetAddressOf()))
        {
            std::cout << "Error while attempting to create a triangle buffer.\n";
            return;
        }
    }
}