#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
struct Framebuffer;
struct shader;
struct Geometry;

enum RenderFlag { Depth = 1};

void setFlag(int flags);

void s0_draw(const Framebuffer &f, shader &s, Geometry &g);

void clearFramebuffer(const Framebuffer &f, bool color = true, bool depth = true);

void setUniform(const shader &s, int location, float value);

void setUniform(const shader &s, int location, int value);

void setUniform(const shader &s, int location, const Texture &value, unsigned slot);


// these will be called  everytime the variadic unpackign recursion takes place
// based upon what unifroms are passed in, the correct funcation will autopmatically
//be calledx in so doing, the appropriate glprogramuniform funtion will also be called
namespace __internal
{
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const Texture val);

	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const glm::vec3 &val);
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const glm::vec4 &val);
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const glm::mat4 &val);
};

//the rec ursive template funtion
// u is the variadic template parameter. eachtime the fuction gets called
// the T parameter (val) will comsume  1 element of the variadic
// so if there is recursion(fuction calling itself), the unioform
// will slowly be eaten by the T parameter.

template<typename T, typename ...U>
void setUniforms(const shader &s, int &loc_io, int &tex_io,
	const T &val, U &&... uniforms)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);

	setUniforms(s, loc_io, tex_io, uniforms...);
}
// this base case, is the last function that gets called. since T is alwasy eating
// valuse  from U, eventually there will be no more U. to insure that we have a valid function,
// we need to have a  base case like so...
template<typename T>
void setUniforms(const shader &s, int &loc_io, int &tex_io,
	const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
}