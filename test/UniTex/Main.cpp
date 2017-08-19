#include "graphics\\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\DrawFunction.h"



int main()
{
	Context context;
	context.init(800, 600);

	Vertex verts[4] =
	{ { { -.5f, -.5f, 0, 1 },{ 1, .3, 1, 1 } },
	{ { .5f, -.5f, 0, 1 },{ 1, 0, 0, .3, } },
	{ { .5f, .5f, 0, 1 },{ 0,1,0,1 } },
	{ { -.5f, .5f, 0, 1 },{ 1 ,1,1,1 } } };


	unsigned idxs[6] = { 0,1,2,3,2,0 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 Position; \n"
		"layout(location = 1) in vec4 color; \n"
		"layout(location = 0) uniform float time;\n"
		"out vec4 vcolor;\n"
		"out vec2 vUV; \n"

		"void main ()\n"
		"{\n"
		"gl_Position = Position;\n"
		//"gl_Position.x += sin(time+ Position.y)/7.0;\n"
		"vcolor = color;\n"
		"vUV  = Position.xy;"
		"}\n";

	const char* fsource = // once per pixel
		"#version 450\n"
		"out vec4 outColor;\n"

		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int tog;\n"
		"layout(location = 2) uniform sampler2D map;\n"
		"flat in vec4 vcolor;\n"
		"in vec2 vUV;\n"

		"void main ()\n"
		"{\n"
		"vec2 uv = vUV;\n"
		"uv.x += sin(time);"
		"outColor = texture(map, uv);\n"
		//"outColor = vec4(1-map,0,0,1);\n"
		/*"if(tog == 1)\n"
		"outColor = 1.0 - vcolor;\n"
		"else outColor = vcolor;\n"
		"outColor.r = (1.0+sin(time+gl_FragCoord.x/50))/2.0;\n"
		*/
		"}\n";


	shader s = makeshader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };

	unsigned char pixels[] = { 255, 0, 255, 
							   255, 255, 0,};

	Texture t_magyel = makeTexture(2, 1, 3, pixels);

	while (context.step())
	{
	

		clearFramebuffer(f);

		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, (int)context.getKey(' '));		
		setUniform(s, 2, t_magyel, 2);

		s0_draw(f, s, g);
	
	}
	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	context.term();

	return 0;
}