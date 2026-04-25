#include "Structs.hlsli"

RWTexture2D<float4> ScreenOutput : register(u0);
RWTexture2D<float> ZBuffer      : register(u1); 

groupshared ProjectedTriangle sharedTriangles[64];
StructuredBuffer<ProjectedTriangle> ProjectedTriangleBuffer : register(t0);


bool IsInBoundingBox(float2 pixelPos, float3 s0, float3 s1, float3 s2);
float3 CalculateEdges(float2 p, float3 s0, float3 s1, float3 s2);
float4 InterpolateColor(float3 tCoord, float4 c1, float4 c2, float4 c3);

[numthreads(8, 8, 1)]
void CSMain(uint3 threadID : SV_DispatchThreadID, uint groupIndex : SV_GroupIndex)
{
    uint tBufferSize, tBufferStride;
    uint2 screenSize;
    uint2 pixelPos = uint2(threadID.xy);

    ScreenOutput.GetDimensions(screenSize.x, screenSize.y);
    ProjectedTriangleBuffer.GetDimensions(tBufferSize, tBufferStride);

    
    for(uint batchStart = 0; batchStart < tBufferSize; batchStart += 64) {
        uint triIndex = batchStart + groupIndex;
        if(triIndex < tBufferSize) {
            sharedTriangles[groupIndex] = ProjectedTriangleBuffer[triIndex];
        }

        GroupMemoryBarrierWithGroupSync();

        uint trisInBatch = min(64, tBufferSize - batchStart);

        for(uint i = 0; i < trisInBatch; i++) {
            ProjectedTriangle t = sharedTriangles[i];

            if(!t.isVisible) continue;

            float3 s0 = t.vertices[0].position;
            float3 s1 = t.vertices[1].position;
            float3 s2 = t.vertices[2].position;
            float4 c0 = t.colors[0].channels;
            float4 c1 = t.colors[1].channels;
            float4 c2 = t.colors[2].channels;

            if(!IsInBoundingBox(pixelPos, s0, s1, s2)) {
                continue; 
            }

            float3 edges = CalculateEdges(pixelPos, s0, s1, s2);

            if((edges.x >= 0 && edges.y >= 0 && edges.z >= 0) || 
               (edges.x <= 0 && edges.y <= 0 && edges.z <= 0)) 
            {
                float tArea = edges.x + edges.y + edges.z;
                float3 tCoord = edges / tArea;
                float pixelDepth = s0.z * tCoord.x + s1.z * tCoord.y + s2.z * tCoord.z;

                if(pixelDepth < ZBuffer[pixelPos]) {
                    if (pixelPos.x < screenSize.x && pixelPos.y < screenSize.y) {
                        ZBuffer[pixelPos] = pixelDepth; 
                        ScreenOutput[pixelPos] = InterpolateColor(tCoord, c0, c1, c2);
                    }
                }
            }
        }

        GroupMemoryBarrierWithGroupSync();
    }
}

bool IsInBoundingBox(float2 pixelPos, float3 s0, float3 s1, float3 s2) 
{
    float minX = min(min(s0.x, s1.x), s2.x);
    float maxX = max(max(s0.x, s1.x), s2.x);
    float minY = min(min(s0.y, s1.y), s2.y);
    float maxY = max(max(s0.y, s1.y), s2.y);

    return (pixelPos.x >= minX && pixelPos.x <= maxX && pixelPos.y >= minY && pixelPos.y <= maxY);
}

float3 CalculateEdges(float2 p, float3 s0, float3 s1, float3 s2) 
{
    float e0 = (p.x - s1.x) * (s2.y - s1.y) - (p.y - s1.y) * (s2.x - s1.x);
    float e1 = (p.x - s2.x) * (s0.y - s2.y) - (p.y - s2.y) * (s0.x - s2.x);
    float e2 = (p.x - s0.x) * (s1.y - s0.y) - (p.y - s0.y) * (s1.x - s0.x);
    
    return float3(e0, e1, e2);
}

float4 InterpolateColor(float3 tCoord, float4 c1, float4 c2, float4 c3) {
    return tCoord.x * c1 + tCoord.y * c2 + tCoord.z * c3;
}