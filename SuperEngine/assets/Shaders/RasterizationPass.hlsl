#include "Structs.hlsli"

RWTexture2D<float4> ScreenOutput : register(u0);
RWTexture2D<float> ZBuffer      : register(u1); 

StructuredBuffer<ProjectedTriangle> ProjectedTriangleBuffer : register(t0);

cbuffer ScreenSize : register(b0) 
{
    uint width;
    uint height;
    float2 padding_screen;
};

float3 CalculateEdges(float2 p, float3 s0, float3 s1, float3 s2);
float4 InterpolateColor(float3 tCoord, float4 c1, float4 c2, float4 c3);

[numthreads(64, 1, 1)]
void CSMain(uint3 threadID : SV_DispatchThreadID)
{
    uint triIndex = threadID.x;
    
    uint tBufferSize, tBufferStride;
    ProjectedTriangleBuffer.GetDimensions(tBufferSize, tBufferStride);

    if(triIndex >= tBufferSize) return;

    ProjectedTriangle t = ProjectedTriangleBuffer[triIndex];

    if(!t.isVisible) return;

    float3 s0 = t.vertices[0].position;
    float3 s1 = t.vertices[1].position;
    float3 s2 = t.vertices[2].position;
    
    float4 c0 = t.colors[0].channels;
    float4 c1 = t.colors[1].channels;
    float4 c2 = t.colors[2].channels;

    int minX = max(0, (int)floor(min(min(s0.x, s1.x), s2.x)));
    int maxX = min((int)width - 1, (int)ceil(max(max(s0.x, s1.x), s2.x)));
    int minY = max(0, (int)floor(min(min(s0.y, s1.y), s2.y)));
    int maxY = min((int)height - 1, (int)ceil(max(max(s0.y, s1.y), s2.y)));

    if(minX > maxX || minY > maxY) return;

    for(int y = minY; y <= maxY; y++)
    {
        for(int x = minX; x <= maxX; x++)
        {
            // +0.5f to center the pixel
            float2 pixelPos = float2((float)x + 0.5f, (float)y + 0.5f); 
            float3 edges = CalculateEdges(pixelPos, s0, s1, s2);

            if((edges.x >= 0 && edges.y >= 0 && edges.z >= 0) || 
               (edges.x <= 0 && edges.y <= 0 && edges.z <= 0)) 
            {
                float tArea = edges.x + edges.y + edges.z;
                
                if (abs(tArea) < 0.0001f) continue;

                float3 tCoord = edges / tArea;
                float pixelDepth = s0.z * tCoord.x + s1.z * tCoord.y + s2.z * tCoord.z;

                uint2 pCoord = uint2(x, y);

                if(pixelDepth < ZBuffer[pCoord]) 
                {
                    ZBuffer[pCoord] = pixelDepth; 
                    ScreenOutput[pCoord] = InterpolateColor(tCoord, c0, c1, c2);
                }
            }
        }
    }
}


float3 CalculateEdges(float2 p, float3 s0, float3 s1, float3 s2) 
{
    float e0 = (p.x - s1.x) * (s2.y - s1.y) - (p.y - s1.y) * (s2.x - s1.x);
    float e1 = (p.x - s2.x) * (s0.y - s2.y) - (p.y - s2.y) * (s0.x - s2.x);
    float e2 = (p.x - s0.x) * (s1.y - s0.y) - (p.y - s0.y) * (s1.x - s0.x);
    
    return float3(e0, e1, e2);
}

float4 InterpolateColor(float3 tCoord, float4 c1, float4 c2, float4 c3) 
{
    return tCoord.x * c1 + tCoord.y * c2 + tCoord.z * c3;
}