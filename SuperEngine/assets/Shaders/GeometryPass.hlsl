#include "Structs.hlsli"

cbuffer ObjectData : register(b0) {
    column_major matrix WorldMatrix; 
};

cbuffer CameraData : register(b1) {
    column_major matrix ViewMatrix;
    column_major matrix ProjectionMatrix;
};

cbuffer ScreenSize : register(b2) {
    uint width;
    uint height;
}

StructuredBuffer<Triangle> TriangleBuffer : register(t0);
RWStructuredBuffer<ProjectedTriangle> ProjectedTriangleBuffer : register(u0);


void ToCameraSpace(Triangle t, out float4 viewVerts[3]);
bool IsBackface(float4 viewVerts[3]);
float3 ProjectToScreen(float4 viewVert, uint2 screenSize);

[numthreads(64,1,1)]
void CSMain(uint3 threadID : SV_DispatchThreadID) {
    uint i = threadID.x;
        
    uint tBufferSize, stride;

    TriangleBuffer.GetDimensions(tBufferSize, stride);


    if(i >= tBufferSize) return;

    Triangle t = TriangleBuffer[i];
    ProjectedTriangle pt = (ProjectedTriangle)0;
    
    float4 viewVerts[3];
    ToCameraSpace(t, viewVerts);
    
    if(IsBackface(viewVerts)) {
        pt.isVisible = 0;
        ProjectedTriangleBuffer[i] = pt;
        return;
    }

    uint2 screenSize = uint2(width, height);
        
    pt.vertices[0].position = ProjectToScreen(viewVerts[0], screenSize);
    pt.vertices[1].position = ProjectToScreen(viewVerts[1], screenSize);
    pt.vertices[2].position = ProjectToScreen(viewVerts[2], screenSize);
    
    
    pt.colors[0].channels = t.colors[0].channels; 
    pt.colors[1].channels = t.colors[1].channels;
    pt.colors[2].channels = t.colors[2].channels;
    
    pt.isVisible = 1; 
    pt.padding = float3(0,0,0);

    
    ProjectedTriangleBuffer[i] = pt;
}


bool IsBackface(float4 viewVerts[3]) 
{
    float3 vec1 = viewVerts[1].xyz - viewVerts[0].xyz;
    float3 vec2 = viewVerts[2].xyz - viewVerts[0].xyz;
    float3 normal = cross(vec1, vec2);
   
    return dot(normal, viewVerts[0].xyz) >= 0.0f; 
}

float3 ProjectToScreen(float4 viewVert, uint2 screenSize) 
{
    float4 clipPos = mul(viewVert, ProjectionMatrix);
    
    if(clipPos.w != 0.0f) {
        clipPos.xyz /= clipPos.w;
    }
    
    float screenX = (clipPos.x + 1.0f) * 0.5f * screenSize.x;
    float screenY = (1.0f - clipPos.y) * 0.5f * screenSize.y;
    
    
    return float3(screenX, screenY, clipPos.z); 
}

void ToCameraSpace(Triangle t, out float4 viewVerts[3]) 
{
    viewVerts[0] = mul(mul(t.vertices[0].position, WorldMatrix), ViewMatrix);
    viewVerts[1] = mul(mul(t.vertices[1].position, WorldMatrix), ViewMatrix);
    viewVerts[2] = mul(mul(t.vertices[2].position, WorldMatrix), ViewMatrix);
}