#ifndef STRUCTS_HLSLI
#define STRUCTS_HLSLI

struct Vertex {
    float4 position;
};
struct Color {
    float4 channels;
};
struct ProjectedVertex {
    float3 position;
    float padding; // 4 bytes padding
};

struct Triangle {
    Vertex vertices[3];
    Color colors[3];
};

struct ProjectedTriangle {
    ProjectedVertex vertices[3];
    Color colors[3];
    int isVisible;
    float3 padding; // 12 bytes padding
};

#endif