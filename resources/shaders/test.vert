//graphics\resources\shaders\test.vert

#version 450
layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 normal;

//layout(location = 1) uniform int idx = 0;
//layout(location = 2) uniform int rows = 4;
//layout(location = 3) uniform int cols = 4;

layout(location = 1) uniform mat4 model;

out vec2 vUV;
out vec4 vNormal;

void main()
{
	//int c = idx/ rows;
	//int r = idx% cols;

	gl_Position = model * position;

	vNormal = model *normal;
	vUV = texCoord;
	//vUV = (vec2(r, c) + texCoord) / vec2(rows,cols);
}

