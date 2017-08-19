#pragma once

struct Framebuffer;
struct shader;
struct Geometry;

void s0_draw(const Framebuffer &f, shader &s, Geometry &g);

void clearFramebuffer(const Framebuffer &f);

void setUniform(const shader &s, int location, float value);

void setUniform(const shader &s, int location, int value);

void setUniform(const shader &s, int location, const Texture &value, unsigned slot);