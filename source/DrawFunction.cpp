
#include "glinc.h"
#include "graphics\RenderObjects.h"
#include "graphics\DrawFunction.h"

void setFlag(int flags)
{
	// depth testing 
	if (flags & RenderFlag::Depth) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);
}

void s0_draw(const Framebuffer &f, shader &s, Geometry &g)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	glViewport(0, 0, f.width, f.height);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}

void clearFramebuffer(const Framebuffer & f, bool color, bool depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glClear(GL_COLOR_BUFFER_BIT * color | GL_DEPTH_BUFFER_BIT * depth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void clearFramebuffer(const Framebuffer &f)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setUniform(const shader &s, int location, int value)
{

	glProgramUniform1i(s.handle, location, value);
}

void setUniform(const shader &s, int location, float value)
{
	
	glProgramUniform1f(s.handle,location,value);
}
void setUniform(const shader &s, int location, const Texture &value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(s.handle, location, slot);
}

namespace __internal
{
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, float val)
	{
		glProgramUniform1f(s.handle, loc_io++, val);

	}
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, int val)
	{
		glProgramUniform1i(s.handle, loc_io++, val);

	}
	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const Texture val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_2D, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}

	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const glm::vec3 &val)
	{
		glProgramUniform3fv(s.handle, loc_io++, 1, glm::value_ptr(val));

	}


	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const glm::vec4 &val)
	{
		glProgramUniform4fv(s.handle, loc_io++, 1, glm::value_ptr(val));

	}



	void t_setUniform(const shader &s, int &loc_io, int &tex_io, const glm::mat4 &val)
	{
		glProgramUniformMatrix4fv(s.handle, loc_io++, 1, 0, glm::value_ptr(val));

	}
};
