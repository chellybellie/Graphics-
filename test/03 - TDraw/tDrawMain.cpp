#include "graphics\\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\DrawFunction.h"
#include "glm\ext.hpp"




int main()
{
	Context context;
	context.init(800, 600);

	Vertex verts[4] =
	{ { { -.5f, -.5f, 0, 1 },{ 1, .3, 1, 1 } },
	{ { .5f, -.5f, 0, 1 },{ 1, 0, 0, .3, } },
	{ { .5f, .5f, 0, 1 },{ 0,1,0,1 } },
	{ { -.5f, .5f, 0, 1 },{ 1 ,1,1,1 } } };

	unsigned idxs[6] = { 0,1,2,0,3,2 };

	unsigned char pixels[] = { 255, 0, 255,
		255, 255, 0, };



	Geometry g = makeGeometry(verts, 4, idxs, 6);
	Texture t_magyel = makeTexture(2, 1, 3, pixels);

	Framebuffer f = { 0, 800, 600 };


	// red == {1,0,0,1}
	// greend == {0,1,0,1}
	// blue = {0,0,1,1}


	const char* vsource = // once per vertex
		"#version 450\n"
		"layout(location = 0) in vec4 Position; \n"
		"layout(location = 1) in vec2 uv; \n"
		"layout(location = 6) uniform mat4 model;\n"


		"out vec2 vUV; \n"

		"void main ()\n"
		"{\n"

		"gl_Position = model * Position;\n"
		"vUV  = Position.xy;"

		"}\n";

	const char* fsource = // once per pixel
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;\n"

		"layout(location = 0) uniform sampler2D map;\n"
		"layout(location = 1) uniform float time; "
		"layout(location = 2) uniform int GetKey;\n"
		"layout(location = 3) uniform int Key1;\n"
		"layout(location = 4) uniform int Key2;\n"
		"layout(location = 5) uniform int Key3;\n"



		"uniform vec4 Red = {1,0,0,1};\n" // w
		"uniform vec4 Green = {0,1,0,1};\n" // a
		"uniform vec4 Blue = {0,0,1,1};\n" //s


		"void main ()\n"
		"{\n"

		"outColor = texture(map, vUV);\n"
		"outColor *= Red*Key1 + Green*Key2 + Blue*Key3; \n"

		"}\n";


	shader s = makeshader(vsource, fsource);


	while (context.step())
	{
		float time = (float)context.getTime();
		clearFramebuffer(f);
		glm::mat4 mod1 = glm::translate(glm::vec3(.5, 0, 0)) *
			glm::scale(glm::vec3(.5, sin(time), 1)) *
			glm::rotate(time, glm::vec3(0.f, 0.f, 1.f));

		glm::mat4 mod2 = glm::translate(glm::vec3(.5, 0, 0)) *
			glm::scale(glm::vec3(.5, sin(time), 1)) *
			glm::rotate(time, glm::vec3(0.f, 0.f, 1.f));

		int loc = 0, tex = 0;
		setUniforms(s, loc, tex, t_magyel,
			(float)context.getTime(),
			(int)context.getKey(' '),
			(int)context.getKey('W'),
			(int)context.getKey('A'),
			(int)context.getKey('S'),
			mod1*mod2);
		s0_draw(f, s, g);

		loc = 0, tex = 0;
		setUniforms(s, loc, tex, t_magyel,
			(float)context.getTime(),
			(int)context.getKey(' '),
			(int)context.getKey('W'),
			(int)context.getKey('A'),
			(int)context.getKey('S'),
			mod2);
		s0_draw(f, s, g);

	}
	freeTexture(t_magyel);

	freeGeometry(g);
	freeShader(s);

	context.term();

	return 0;
}