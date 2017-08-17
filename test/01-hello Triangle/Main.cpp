
#include "graphics\\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\DrawFunction.h"


int main()
{
	Context context;
	context.init(800,600);

	Vertex verts[4] =
	{ { { -.5f, -.5f, 0, 1  }, {1, .3, 1, 1}},
	  { { .5f, -.5f, 0, 1   }, {1, 0, 0, .3,}},
	  { {  .5f, .5f, 0, 1   }, {0,1,0,1}},
	  { { -.5f, .5f, 0, 1   }, {1 ,1,1,1}} };
	

	unsigned idxs[6] = { 0,1,2,3,2,0 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position; \n"
		"layout(location = 1) in vec4 color; \n"

		"out vec4 vpos; \n"
		"out vec4 vcolor;\n"
		"void main ()\n"
		"{\n"
		"vpos = position; \n"
		"gl_Position = position; vcolor = color;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"in vec4 vpos;\n"
		"in vec4 vcolor;"
		"out vec4 outColor;\n"
		"void main ()\n"
		"{\n"
		"outColor = vcolor;\n"
		"}\n";


	shader s = makeshader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };

	while (context.step())
	{
		s0_draw(f, s, g);
	}
	freeGeometry(g);
	freeShader(s);
	context.term();
	return 0;
}