#pragma once

#include "glm/glm.hpp"
#include "glm\ext.hpp"
#include "RenderObjects.h"

struct Camera
{	
	glm::mat4 proj;
	glm::mat4 view;

};

struct specgloss
{
	Geometry geo;
	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;
};

struct standeredLight
{
	glm::vec3 dir;
	glm::vec4 color;
	float intensity;
	glm::vec4 ambient;
	int type;
};

struct DirectionalLight
{
	glm::vec3 target;
	float range;

	glm::vec3 direction;

	glm::mat4 getproj() const
	{
		return glm::ortho<float>(-range, range, -range, range, -range, range);
	} //0
	glm::mat4 getview() const
	{
		glm::lookAt(-direction + target, target, glm::vec3(0, 1, 0));
	} // 1

	glm::vec4 color;
	float intensity;
};


namespace __internal
{
	void t_setUniform(const shader &s, int &loc_io, int & tex_io, const Camera & val);
	void t_setUniform(const shader &s, int &loc_io, int & tex_io, const specgloss & val);
	void t_setUniform(const shader &s, int &loc_io, int & tex_io, const DirectionalLight & val);
}