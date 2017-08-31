#include "graphics\\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\DrawFunction.h"
#include "glm\ext.hpp"
#include "graphics\load.h"


int main()
{
	Context context;
	context.init(800, 800);
	Vertex vquad[4] = { { { -1, -1, 0, 1 },{ 1,1,1,1 },{ 0,0 } },
	{ { 1, -1, 0, 1 },{ 1,0,1,1 },{ 1,0 } },
	{ { 1,  1, 0, 1 },{ 1,0,0,1 },{ 1,1 } },
	{ { -1,  1, 0, 1 },{ 0,0,1,1 },{ 0,1 } } };
	unsigned quadidx[6] = { 0,1,3,1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/sphere.obj");
	Texture tex = loadTexture("../../resources/textures/soulspear_diffuse.tga");

	shader sq = loadShader("../../resources/shaders/test.vert",
								"../../resources/shaders/test.frag");
	
	//shader scube = loadShader("../../resources/shaders/cube.vert",
								//"../../resources/shaders/cube.frag");
	Framebuffer screen = { 0, 800,800 };

	

	while (context.step())
	{
		clearFramebuffer(screen);
		glm::mat4 body1, orbit2, body2;

		body1 = glm::rotate((float)context.getTime(), glm::vec3(1, 1, 1))
							* glm::scale(glm::vec3(.5, .5, .5));

		body2 = glm::rotate((float)context.getTime(), glm::vec3(1, 1, 1))
						* glm::scale(glm::vec3(.2, .2, .2));
		
		orbit2 = glm::rotate((float)context.getTime(), glm::vec3(0, 1, 0)) *
			glm::translate(glm::vec3(.5, 0, 0));

		setFlag(RenderFlag::Depth);
		int loc = 0, tslot = 0;			
		setUniforms(sq, loc, tslot, tex, body1);
		s0_draw(screen, sq, cube);

		loc = 0, tslot = 0;
		setUniforms(sq, loc, tslot, tex, orbit2 * body2);
		s0_draw(screen, sq, cube);
	}

	return 0;
}












