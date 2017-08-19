#pragma once

struct Vertex;

struct Geometry
{
	unsigned 
		handle,   //vertext array object
		vbo,	 // vertex buffer
		ibo,    // index buffer
		size;  // how many indices make up this model
};


Geometry makeGeometry(const Vertex *verts, size_t vsize,
				      const unsigned *idxs, size_t isize);

void freeGeometry(Geometry &g);

struct shader
{
	unsigned handle;
};
struct Framebuffer
{
	unsigned handle, width, height;
 };
struct Texture
{
	unsigned handle;
};

Texture makeTexture(unsigned w, unsigned h, unsigned c,
		const unsigned char *pixels);
shader makeshader(const char *vert_src, const char *frag_src);
void freeShader(shader &s);
void freeTexture(Texture &t);