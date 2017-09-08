#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\DrawFunction.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include "graphics\GameObject.h"

int main()
{
	Context context;
	context.init();

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	shader standard = loadShader("../../resources/shaders/standered.vert",
								 "../../resources/shaders/standered.frag");

	Framebuffer screen = { 0, 800, 600 };


	////////////////////////
	/// Model Data
	specgloss sg;
	sg.geo = loadGeometry("../../resources/models/soulspear.obj");
	sg.model;

	sg.normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	sg.diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	sg.specular = loadTexture("../../resources/textures/soulspear_specular.tga");
    sg.gloss = 4.0f;  


	////////////////////////
	/// Model Data2
	specgloss sg2;
	sg2.geo = loadGeometry("../../resources/models/soulspear.obj");
	sg2.model;

	sg2.normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	sg2.diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	sg2.specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	sg2.gloss = 4.0f;

	//////////////////////////
	// Camera Data
	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0, 2, 3),
		glm::vec3(0, 2, 0),
		glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	//////////////////////////
	// Light
	standeredLight sl;
	sl.dir = glm::normalize(glm::vec3(1, -1, -1));
	sl.color = glm::vec4(1, .5, .9, 1);
	sl.intensity = 1.0;
	sl.ambient = glm::vec4(.02, .3, .3, 1);
	sl.type = 0;



	while (context.step())
	{
		float time = context.getTime();
		sg.model = glm::rotate(time / 2, glm::vec3(0, 1, 0));

		///////////////////////////////
		// buffer pass
		clearFramebuffer(screen);
		setFlag(RenderFlag::Depth);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam.proj, cam.view,	// Camera data!
			sg.model, sg.diffuse, sg.specular, sg.normal, sg.gloss, // model data!
			sl.dir, sl.color, sl.intensity, sl.ambient, sl.type		  // light data!
		);

		s0_draw(screen, standard, sg.geo);

		///////////////////////////////
		// FSQ pass

	}
	context.term();
	return 0;
}