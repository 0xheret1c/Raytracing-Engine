#include "./Polygon.h"

Polygon::Polygon(Vector verts[3])
{
	for (size_t i = 0; i < 3; i++)
	{
		this->vertex[i].x = verts[i].x;
		this->vertex[i].y = verts[i].y;
		this->vertex[i].z = verts[i].z;
	}
}

