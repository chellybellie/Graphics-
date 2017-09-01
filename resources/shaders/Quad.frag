#version 450


in vec2 vUV;

layout(location = 0) uniform sampler2D map;

out vec4 outColor;


void main()
{
	outColor = texture(map, vUV);
}

vec4 crossblur(in sampler@D map, in vec2 uv, int it)
{
	vec2 sDim = textureSize(map, 0).xy;
	vec4 retval = vec4(0,0,0,0);

	for(int i = -it; i <= it; ++i)
	{
	 retval += texture(map, uv, + vec2(i,0)/sDim);
	 retval += texture(map, uv, + vec2(0,i)/sDim);
	 }

} 