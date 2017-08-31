#include "graphics\\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\DrawFunction.h"
#include "glm\ext.hpp"
#include "graphics\load.h"



int main()
{
	Context context;
	context.init(800, 600);

	Geometry ss_geo = loadGeometry("../resources/models/soulspear.obj");

	Texture ss_diffuse = loadTexture("../resources/textures/soulspear_diffuse.tga");

	shader mvplite = loadShader("../resources/shaders/mvplite.vert",
								"../resources/shaders/mvplite.frag");
	Framebuffer screen = { 0,800,600 };
	 

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
	glm::mat4 go_model;


	while (context.step())
	{
		clearFramebuffer(screen);

		setFlag(RenderFlag::Depth);

		int loc = 0, slot = 0;
		setUniforms(mvplite, loc, slot, cam_proj, cam_view, go_model, ss_diffuse);
		//cam_view = glm::lookAt(glm::vec3(0, 3, -4), targetPosition, glm::vec3(0, 1, 0));
		s0_draw(screen, mvplite, ss_geo);

	}


	return 0;
}


