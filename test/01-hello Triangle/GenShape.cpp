#include "GenShape.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "glm\glm.hpp"


Geometry makeNgeo(size_t sides, float r)
{
	unsigned vsize = 0;
	unsigned isize = 0;
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;
	return ret;

}  