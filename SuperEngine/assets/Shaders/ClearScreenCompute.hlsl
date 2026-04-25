RWTexture2D<float4> ScreenOutput : register(u0);
RWTexture2D<float> ZBuffer : register(u1);

[numthreads(8, 8, 1)]
void CSMain(uint3 threadID : SV_DispatchThreadID){
    ScreenOutput[threadID.xy] = float4(0, 0.506, 0.722, 1);
    ZBuffer[threadID.xy] = 1.0f;
}