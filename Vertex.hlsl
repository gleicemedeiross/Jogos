cbuffer ConstantBuffer
{
	float4x4 WorldViewProj;
}

struct VertexIn
{
	float3 Pos   : POSITION;
	float4 Color : COLOR;
	float2 Tex   : TEXCOORD;	
};

struct VertexOut
{
	float4 Pos   : SV_POSITION;
	float4 Color : COLOR;
	float2 Tex   : TEXCOORD;	
};

VertexOut main( VertexIn vIn )
{
	VertexOut vOut;

	// transforma v�rtices para coordenadas da tela
	vOut.Pos = mul(float4(vIn.Pos, 1.0f), WorldViewProj);
	
	// mant�m as cores inalteradas
	vOut.Color = vIn.Color;

	// mant�m as coordenadas da textura inalteradas
	vOut.Tex = vIn.Tex;

	return vOut;
}