// graphics\resources\shaders\test.frag

#version 450
out vec4 outColor;
in vec2 vUV;
in vec4 vNormal;

layout(location = 0) uniform sampler2D map;

void main()
{
	outColor = dot(vNormal, -normalize(vec4(1,0,1,0))) * texture(map, vUV.xy);
	//outColor = vec4(vUV,0,1);
}