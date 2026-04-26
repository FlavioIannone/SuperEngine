#include "Structs.hlsli"

cbuffer CameraData : register(b0) // 128 byte (View + Proj)
{
    float4x4 viewMatrix;
    float4x4 projMatrix;
};

cbuffer ScreenSize : register(b1) // 16 byte
{
    uint width;
    uint height;
    float2 padding_screenSize; 
};

cbuffer ObjectIndex : register(b2) // 16 byte
{
    uint objectIndex;
    float3 padding_objectIndex;
};

// Mesh
StructuredBuffer<Triangle> TriangleBuffer : register(t0);
// Transformations matrices
StructuredBuffer<float4x4> ObjectsData : register(t1);

// Projected Triangles UAV
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
    float4 clipPos = mul(viewVert, projMatrix);
    
    if(clipPos.w != 0.0f) {
        clipPos.xyz /= clipPos.w;
    }
    
    float screenX = (clipPos.x + 1.0f) * 0.5f * screenSize.x;
    float screenY = (1.0f - clipPos.y) * 0.5f * screenSize.y;
    
    return float3(screenX, screenY, clipPos.z); 
}

void ToCameraSpace(Triangle t, out float4 viewVerts[3]) 
{
    float4x4 worldMatrix = ObjectsData[objectIndex];
   
    viewVerts[0] = mul(mul(t.vertices[0].position, worldMatrix), viewMatrix);
    viewVerts[1] = mul(mul(t.vertices[1].position, worldMatrix), viewMatrix);
    viewVerts[2] = mul(mul(t.vertices[2].position, worldMatrix), viewMatrix);
}