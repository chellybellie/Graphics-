#include "graphics\GameObject.h"
#include "graphics\DrawFunction.h"





void __internal::t_setUniform(const shader & s, int & loc_io, int & tex_io, const Camera & val)
{													// LAYOUT POSITION?
	t_setUniform(s, loc_io, tex_io, val.proj);      // 0
	t_setUniform(s, loc_io, tex_io, val.view);      // 1
 }

void __internal::t_setUniform(const shader & s, int & loc_io, int & tex_io, const specgloss & val)
{													// LAYOUT POSITION?
	t_setUniform(s, loc_io, tex_io, val.model);		//0 MATRIX

	t_setUniform(s, loc_io, tex_io, val.diffuse);   //1 TEXTURE
	t_setUniform(s, loc_io, tex_io, val.specular);  //2 TEXTURE
	t_setUniform(s, loc_io, tex_io, val.normal);	//3 TEXTURE
	t_setUniform(s, loc_io, tex_io, val.gloss);		//4 FLOAT
}

void __internal::t_setUniform(const shader & s, int & loc_io, int & tex_io, const DirectionalLight & val)
{													// LAYOUT POSITION?
	t_setUniform(s, loc_io, tex_io, val.getproj);   // 0 
	t_setUniform(s, loc_io, tex_io, val.getview);   // 1
	t_setUniform(s, loc_io, tex_io, val.color);     // 2
	t_setUniform(s, loc_io, tex_io, val.intensity); // 3
}