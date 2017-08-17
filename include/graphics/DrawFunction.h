#pragma once

struct Framebuffer
{
	unsigned handle;
	unsigned width, height;

};
void s0_draw(const Framebuffer &f, shader &s, Geometry &g);